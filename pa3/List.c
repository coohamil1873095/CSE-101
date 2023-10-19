//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
//  List.h
//  Implementation file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
    ListElement data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data) {
    Node N = malloc(sizeof(NodeObj));
    assert(N);
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
    if (pN && *pN) {
        (*pN)->prev = NULL;
        (*pN)->next = NULL;
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    assert(L);
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}
// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
void freeList(List* pL) {
    if (pL && *pL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Error functions ------------------------------------------------------------

void checkExist(List L, char* function) {
    if(!L){
        fprintf(stderr, "List Error: calling %s() on NULL List reference\n", function);
        exit(EXIT_FAILURE);
    }
}
void checkLength(List L, char* function) {
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling %s() on an empty List\n", function);
        exit(EXIT_FAILURE);
    }
}
void checkIndex(List L, char* function) {
    if (L->index < 0) {
        fprintf(stderr, "List Error: calling %s() on List with invalid cursor index\n", function);
        exit(EXIT_FAILURE);
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
    checkExist(L, "length");
    return L->length;
}
// Returns index of cursor element if defined, -1 otherwise. 
int index(List L) {
    checkExist(L, "index");
    return L->cursor ? L->index : -1;
}
// Returns front element of L. Pre: length()>0
int front(List L) {
    checkExist(L, "front");
    checkLength(L, "front");
    return L->front->data;
}
// Returns back element of L. Pre: length()>0 
int back(List L) {
    checkExist(L, "back");
    checkLength(L, "back");
    return L->back->data;
}
// Returns cursor element of L. Pre: length()>0, index()>=0 
int get(List L) {
    checkExist(L, "get");
    checkLength(L, "get");
    checkIndex(L, "get");
    return L->cursor->data;
}
// Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
bool equals(List A, List B) {
    if(!A || !B){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    if (length(A) != length(B)) {
        return false;
    }
    Node ANode = A->front;
    Node BNode = B->front;
    while (ANode) {
        if (ANode->data != BNode->data) {
            return false;
        }
        ANode = ANode->next;
        BNode = BNode->next;
    }
    return true;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
    checkExist(L, "clear");
    Node curr = L->front;
    Node prev = L->front;
    while (curr) {
        prev = curr;
        curr = curr->next;
        freeNode(&prev);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}
// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void set(List L, int x) {
    checkExist(L, "set");
    checkLength(L, "set");
    checkIndex(L, "set");
    L->cursor->data = x;
}
// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing. 
void moveFront(List L) {
    checkExist(L, "moveFront");
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}
// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing. 
void moveBack(List L) {
    checkExist(L, "moveBack");
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}
// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L) {
    checkExist(L, "movePrev");
    if (L->cursor) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }
        else {
            L->cursor = L->cursor->prev;
            L->index -= 1;
        }
    }
}
// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L) {
    checkExist(L, "moveNext");
    if (L->cursor) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        }
        else {
            L->cursor = L->cursor->next;
            L->index += 1;
        }
    }
}
// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x) {
    checkExist(L, "prepend");
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = L->back = N;
        L->index = 0;
    }
    else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    L->length += 1;
    L->index += 1;
}
// Insert new element into L. If L is non-empty,
 // insertion takes place after back element. 
void append(List L, int x) {
    checkExist(L, "append");
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = L->back = N;
        L->index = 0;
    }
    else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length += 1;
}
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    checkExist(L, "insertBefore");
    checkLength(L, "insertBefore");
    checkIndex(L, "insertBefore");
    Node N = newNode(x);
    if (L->cursor == L->front) {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    else {
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
    }
    L->index += 1;
    L->length += 1;
}
// Insert new element after cursor.
 // Pre: length()>0, index()>=0 
void insertAfter(List L, int x) {
    checkExist(L, "insertAfter");
    checkLength(L, "insertAfter");
    checkIndex(L, "insertAfter");
    Node N = newNode(x);
    if (L->cursor == L->back) {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    else {
        N->prev = L->cursor;
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        L->cursor->next = N;
    }
    L->length += 1;
}
// Delete the front element. Pre: length()>0 
void deleteFront(List L) {
    checkExist(L, "deleteFront");
    checkLength(L, "deleteFront");
    if (L->length == 1) {
        freeNode(&(L->front));
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    }
    else {
        Node temp = L->front->next;
        temp->prev = NULL;
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }
        else {
            L->index -= 1;
        }
        freeNode(&(L->front));
        L->front = temp;
    }
    L->length -= 1;
}
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    checkExist(L, "deleteBack");
    checkLength(L, "deleteBack");
    if (L->length == 1) {
        freeNode(&(L->back));
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    }
    else {
        Node temp = L->back->prev;
        temp->next = NULL;
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        }
        freeNode(&(L->back));
        L->back = temp;
    }
    L->length -= 1;
}
// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0 
void delete(List L) {
    checkExist(L, "delete");
    checkLength(L, "delete");
    checkIndex(L, "delete");
    if (L->length == 1) {
        freeNode(&(L->cursor));
        L->front = L->back = L->cursor = NULL;
    }
    else {
        if (L->cursor == L->front) {
            L->cursor->next->prev = NULL;
            L->front = L->cursor->next;
        }
        else if (L->cursor == L->back) {
            L->cursor->prev->next = NULL;
            L->back = L->cursor->prev;
        }
        else {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
        }
        freeNode(&(L->cursor));
    }
    L->index = -1;
    L->length -= 1;
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
 // with front on left.
void printList(FILE* out, List L) {
    checkExist(L, "printList");
    Node temp = L->front;
    while (temp) {
        fprintf(out, FORMAT" ", temp->data);
        temp = temp->next;
    }
}
// Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
 // regardless of the state of the cursor in L. The state
 // of L is unchanged.
List copyList(List L) {
    checkExist(L, "copyList");
    List newL = newList();
    Node temp = L->front;
    while (temp) {
        append(newL, temp->data);
        temp = temp->next;
    }
    if (!newL->front) {
        newL->cursor = NULL;
        newL->index = -1;
    }
    return newL;
}

// Optional -------------------------------------------------------------------

// Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.
List concatList(List A, List B) {
    if(!A || !B){
        printf("List Error: calling concatList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List newL = copyList(A);
    Node temp = B->front;
    while (temp) {
        append(newL, temp->data);
        temp = temp->next;
    }
    if (!newL->front) {
        newL->cursor = NULL;
        newL->index = -1;
    }
    return newL;
}
