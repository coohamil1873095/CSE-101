//-----------------------------------------------------------------------------
//  Connor Hamilton
//  coohamil 
//  2023 Fall PA5
//  List.c
//  Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------
    
// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

// Copy constructor.
List::List(const List& L) {
    // make this an empty List
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = pos_cursor = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    // load elements of L into this List
    Node* N = L.backDummy->prev;
    while (N != L.frontDummy) {
        insertAfter(N->data);
        N = N->prev;
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (num_elements == 0) {
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (num_elements == 0) {
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor == 0) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    if (num_elements == 0) {
        return;
    }
    Node* curr = frontDummy->next;
    Node* prev = curr;
    while (curr != backDummy) {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    afterCursor = frontDummy->next;;
    beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    pos_cursor += 1;
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor == 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    pos_cursor -= 1;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;

    if (pos_cursor == 0) { 
        frontDummy->next = N;
    }
    else {
        beforeCursor->next = N;
    }
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;

    if (pos_cursor == num_elements) { 
        backDummy->prev = N;
    }
    else {
        afterCursor->prev = N;
    }
    beforeCursor->next = N; 
    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if( pos_cursor >= num_elements ){
        throw std::range_error("List: peekPrev(): cursor at back");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if( pos_cursor == 0 ){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if( pos_cursor >= num_elements ){
        throw std::range_error("List: peekPrev(): cursor at back");
    }
    afterCursor->next->prev = beforeCursor;
    beforeCursor->next = afterCursor->next;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    num_elements -= 1;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if( pos_cursor == 0 ){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    beforeCursor->prev->next = afterCursor;
    afterCursor->prev = beforeCursor->prev;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    num_elements -= 1;
    pos_cursor -= 1;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    int ret = -1;
    while (afterCursor != backDummy) {
        pos_cursor += 1;
        afterCursor = afterCursor->next;
        beforeCursor = beforeCursor->next;
        if (beforeCursor->data == x) {
            ret = pos_cursor;
            break;
        }
    }
    return ret;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    int ret = -1;
    while (beforeCursor != frontDummy) {
        pos_cursor -= 1;
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        if (afterCursor->data == x) {
            ret = pos_cursor;
            break;
        }
    }
    return ret;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    Node* N = frontDummy->next;
    int pass = 0;
    while (N != backDummy) {
        Node* M = N->next;
        Node* delN = nullptr;
        int index = pass + 1;
        while (M != backDummy) {
            delN = M;
            M = M->next;
            if (delN->data == N->data) {
                delN->prev->next = delN->next;
                delN->next->prev = delN->prev;
                delete delN;
                num_elements -= 1;
                if (index < pos_cursor) {
                    if (index == pos_cursor - 1) {
                        beforeCursor = M->prev;
                        beforeCursor->next = M;
                    }
                    pos_cursor -= 1;
                    index -= 1;
                }
                else if (index == pos_cursor) {
                    afterCursor = M;
                    afterCursor->prev = M->prev;
                }
            }
            index += 1;
        }
        N = N->next;
        pass += 1;
    }
}
    
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List J;
    Node* N = backDummy->prev;
    Node* M = L.backDummy->prev;
    while (M != L.frontDummy) {
        J.insertAfter(M->data);
        M = M->prev;
    }
    while (N != frontDummy) {
        J.insertAfter(N->data);
        N = N->prev;
    }
    return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string s = "(";
    Node* N = frontDummy->next;
    if (N != backDummy) {
        s += std::to_string(N->data);
        N = N->next;
    }

    while (N != backDummy) {
        s += ", " + std::to_string(N->data);
        N = N->next;
    }
    s += ")";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = (num_elements == R.num_elements);
    Node* N = frontDummy->next;
    Node* M = R.frontDummy->next;

    while (eq && N != backDummy && M != R.backDummy) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    eq = eq && (N == this->backDummy) && (M == R.backDummy);

    return eq;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if( this != &L ){ // not self assignment
        clear();

        Node* N = L.backDummy->prev;
        while (N != L.frontDummy) {
            insertAfter(N->data);
            N = N->prev;
        }

        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
    }

    // return this with the new data installed
    return *this;
}