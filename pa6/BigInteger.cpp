//-----------------------------------------------------------------------------
//  Connor Hamilton
//  coohamil 
//  2023 Fall PA6
//  BigInteger.c
//  Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

// global constants
ListElement base = 100;     // 1000000000
int power = 2;            // 9

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
    if (x == 0) { signum = 0; }
    else { signum = (x < 0) ? -1 : 1; }

    x = std::abs(x);
    long temp = x % base;
    while (x > 0) {
        digits.insertAfter(temp);
        x /= base;
        temp = x % base;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    
    // remove leading/trailing whitespace
    int temp = s.find_first_not_of(' ');
    if (temp == -1) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    s = s.substr(temp);
    s = s.substr(0, s.find_last_not_of(' ') + 1);

    std::string nums = "";
    int pos = 0;
    int offset = 0;

    if (s[0] == '+' || s[0] == '-') {
        signum = (s[0] == '+') ? 1 : -1;
        offset = 1;
    }

    // only + or -
    if (offset && s.length() == 1) { 
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    // check leading zeros
    temp = s.find_first_not_of('0', offset);
    // only zeros
    if (temp == -1) {
        signum = 0;
        return;
    }
    s = s.substr(temp);

    // set offset back to 0 if leading zeros were removed
    if (temp != 0) { offset = 0; }

    for (int i = s.length() - 1; i >= 0 + offset; i--) {
        //std::cout << s[i];
        
        // invalid character
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        // character is 0-9
        else {
            nums.insert(0, std::string(1, s[i]));
            pos += 1;
        }

        // cutoff for inserting into digits
        if (pos == power) {
            long x = stol(nums);
            digits.insertAfter(x);

            nums.clear();
            pos = 0;
        }

    }
    // leftover nums
    if (nums.length() > 0) {
        long x = stol(nums);
        digits.insertBefore(x);
    }
    // set signum if haven't already
    if (signum != -1) { signum = 1; }

    std::cout << digits << std::endl;
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns 1, -1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    List thisL = digits;
    List paraL = N.digits;
    
    if (signum == 1 && N.signum == -1) { return 1; }
    else if (signum == -1 && N.signum == 1) { return -1; }

    if (thisL.length() > paraL.length()) { return 1; }
    else if (thisL.length() < paraL.length()) { return -1; }

    thisL.moveFront();
    paraL.moveFront();
    while (thisL.position() < thisL.length() && paraL.position() < paraL.length()) {
        long thisNum = thisL.moveNext();
        long paraNum = paraL.moveNext();
        if (thisNum > paraNum) { return 1; }
        else if (thisNum < paraNum) { return -1; }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum != 0) {
        signum = (signum == -1) ? 1 : -1;
    }
}

// BigInteger Arithmetic helper functions ----------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * -1);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    S.clear();
    A.moveBack();
    B.moveBack();

    if (sgn == -1) { negateList(B); }

    // add elements together
    while (A.position() > 0 && B.position() > 0) { S.insertAfter(A.movePrev() + B.movePrev()); }
    // deal with leftovers
    while (A.position() > 0) { S.insertAfter(A.movePrev()); }
    while (B.position() > 0) { S.insertAfter(B.movePrev()); }

    // remove leading zeros
    S.moveFront();
    while (S.position() < S.length()) {
        if (S.moveNext() != 0) {
            break;
        }
        S.eraseBefore();
    }


    // std::cout << S << std::endl;
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
    // if input is zero
    if (L.length() == 0) {
        return 0;
    }
    
    int carry, sign;
    carry = sign = 0;
    L.moveBack();

    // negate if front is negative
    if (L.front() < 0) {
        negateList(L);
        sign = -1;
    }

    // set to remainder and save quotient as carry
    while (L.position() > 0) {
        long x = L.peekPrev() + carry;
        L.setBefore((x + base) % base);      // add base first to deal with negatives
        carry = (x >= 0) ? (x / base) : -1;   // set to -1 if number used to be negative
        L.movePrev();
    }
    // if leftover carry
    if (carry >= 1) {
        L.insertBefore(carry);
    }
    if (sign != -1) { sign = carry; }        // set sign to carry unless previously negated

    // return 0 if bigint is 0, otherwise sign
    L.moveFront();
    while (L.position() < L.length()) {
        if (L.moveNext() != 0) {
            break;
        }
        L.eraseBefore();
    }
    if (L.position() == L.length()) { 
        return 0; 
    }

    // std::cout << L << std::endl;
    // std::cout << "sign: " << sign << std::endl;

    return ((sign >= 0) ? 1 : -1);
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * m);
        L.moveNext();
    }
}



// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger ret;
    List& sum = ret.digits;
    List N_L = N.digits;

    if (signum == -1 && N.signum != 1) {
        sumList(sum, digits, N_L, 1);
        normalizeList(sum);
        ret.signum = -1;
    }
    else if (signum == -1 && N.signum == 1) {
        sumList(sum, digits, N_L, -1);
        negateList(sum);
        ret.signum = normalizeList(sum);
    }
    else {
        sumList(sum, digits, N_L, N.signum);
        ret.signum = normalizeList(sum);
    }
    
    //std::cout << ret.signum << std::endl;

    return ret;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger ret;
    List& diff = ret.digits;
    List N_L = N.digits;

    
    // x - y
    // x - (-y) -> x + y
    // (-x) - y 
    // (-x) - (-y) -> (-x) + y

    if (signum != -1 && N.signum != -1) { 
        sumList(diff, digits, N_L, -1);
        ret.signum = normalizeList(diff); 
    }
    else if (signum != -1 && N.signum == -1) { 
        sumList(diff, digits, N_L, 1);
        ret.signum = normalizeList(diff); 
    }
    else if (signum == -1 && N.signum != -1) { 
        sumList(diff, digits, N_L, 1);
        normalizeList(diff);
        ret.signum = -1;
    }
    else if (signum == -1 && N.signum == -1) { 
        sumList(diff, digits, N_L, -1);
        negateList(diff);
        ret.signum = normalizeList(diff);
    }

    //std::cout << ret.digits << std::endl;
    //std::cout << ret.signum << std::endl;
    
    return ret;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger ret;

    // set resulting sign
    if (signum == 0 || N.signum == 0) { return ret; }
    if (signum == -1 || N.signum == -1) { ret.signum = -1; }
    else { ret.signum = 1; }

    List& sum = ret.digits;
    List copyL;
    List N_L = N.digits;
    int shift = 0;

    N_L.moveBack();

    // std::cout << digits << std::endl;
    // std::cout << N.digits << std::endl;
    // std::cout << "length: " << digits.length() << std::endl;

    for (int i = 0; i < N_L.length(); i++) {
        
        copyL = digits;
        
        scalarMultList(copyL, N_L.peekPrev());

        copyL.moveBack();
        for (int j = 0; j < shift; j++) {
            copyL.insertBefore(0);
        }

        //std::cout << "scalar: " << copyL << std::endl;

        sumList(sum, sum, copyL, 1);

        //std::cout << "sum: " << sum << std::endl;

        normalizeList(sum);

        //std::cout << "normalize: " << sum << std::endl;

        shift += 1;
        N_L.movePrev();
    }

    //std::cout << ret.digits << std::endl;

    return ret;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s = "";
    if (signum == 0) { 
        s += '0'; 
        return s;
    }
    else if (signum == -1) { s += '-'; }
    
    digits.moveFront();
    while (digits.position() < digits.length()) {
        long x = digits.peekNext();
        int len = power - std::to_string(x).length();
        // insert leading zeros
        if (digits.position() != 0 && len != 0) {
            for (int i = 0; i < len; i++) {
                s += '0';
            }
        }
        s += std::to_string(digits.moveNext());
    }
    return s;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int ret = A.compare(B);
    return (ret == 0 || ret == -1);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int ret = A.compare(B);
    return (ret == 0 || ret == 1);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
