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

using namespace std;

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
}

// Class Constructors & Destructors ----------------------------------------
    
// Creates new List in the empty state.
List::List() {
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    num_elements = 0;
    pos_cursor = 0;
}

// Copy constructor.
List::List(const List& L) {
    // make this an empty List
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    num_elements = 0;
    pos_cursor = 0;

    // load elements of L into this List
    Node* N = L.backDummy;
    while( N!=nullptr ){
        this->insertAfter(N->data);
        N = N->prev;
    }
    // std::cout << "***called copy constructor: " << this->to_string() << std::endl;
}

// Destructor
List::~List() {
    clear();
    frontDummy = nullptr;
    backDummy = nullptr;
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
    if( num_elements == 0 ){
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if( num_elements == 0 ){
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->data;
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
    if( pos_cursor >= num_elements ){
        throw std::length_error("List: peekNext(): invalid cursor position");
    }

    Node* N = frontDummy;
    for (int i = 0; i < pos_cursor; i++) {
        N = N->next;
    }
    return N->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if( pos_cursor == 0 ){
        throw std::length_error("List: peekPrev(): invalid cursor position");
    }

    Node* N = frontDummy;
    for (int i = 0; i < pos_cursor - 1; i++) {
        N = N->next;
    }
    return N->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {

}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {

}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {

}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {

}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {

}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {

}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {

}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {

}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {

}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {

}
    
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List J;
    Node* N = this->backDummy;
    Node* M = L.backDummy;
    while( M!=nullptr ){
        J.insertAfter(M->data);
        M = M->prev;
    }
    while( N!=nullptr ){
        J.insertAfter(N->data);
        N = N->prev;
    }
    return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {

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
        // make a copy of Q
        List temp = L;

        // then swap the copy's fields with fields of this
        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(num_elements, temp.num_elements);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}