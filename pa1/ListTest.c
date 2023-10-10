//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA1
//  ListTest.c
//  Tests the List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

void printListDiags(List L) {
    printf("Length: %d Index: %d Front: %d Back: %d\n", length(L), index(L), front(L), back(L));
    printList(stdout, L);
}

int main() {
    List A = newList();
    fprintf(stderr, "hi\n");
    //Test append, prepend, and print functions
    append(A, 1);
    deleteBack(A);
    //printListDiags(A);
    append(A, 2);
    printListDiags(A);
    prepend(A, 3);
    printListDiags(A);

    //Test cursor movement
    moveFront(A);
    printListDiags(A);
    moveBack(A);
    printListDiags(A);
    moveNext(A);
    printListDiags(A);
    moveNext(A);
    printListDiags(A);
    moveFront(A);
    printListDiags(A);
    movePrev(A);
    printListDiags(A);
    moveBack(A);
    movePrev(A);
    printListDiags(A);

    //Test cursor inserts
    set(A, 4);
    printListDiags(A);
    insertBefore(A, 5);
    printListDiags(A);
    insertBefore(A, 6);
    printListDiags(A);
    insertAfter(A, 7);
    printListDiags(A);
    insertAfter(A, 8);
    printListDiags(A);

    //Test delete functions
    deleteFront(A);
    printListDiags(A);
    moveFront(A);
    deleteFront(A);
    printListDiags(A);
    moveBack(A);
    movePrev(A);
    deleteBack(A);
    printListDiags(A);
    deleteBack(A);
    printListDiags(A);
    moveFront(A);
    delete(A);
    printListDiags(A);

    //Test get, equals, and clear
    List B = newList();
    printf("A/B equality: %s\n", equals(A, B) ? "true" : "false");
    append(B, 4);
    printf("A/B equality: %s\n", equals(A, B) ? "true" : "false");
    append(B, 8);
    printf("A/B equality: %s\n", equals(A, B) ? "true" : "false");
    moveFront(A);
    printf("Cursor Element: %d\n", get(A));
    printListDiags(A);
    clear(A);
    printf("Length: %d Index: %d\n", length(A), index(A));
    printList(stdout, A);
    clear(B);
    printf("A/B equality: %s\n", equals(A, B) ? "true" : "false");

    //Test copyList and concatList
    append(A, 1);
    append(A, 2);
    append(A, 3);
    moveFront(A);
    printf("List A: \n");
    printListDiags(A);
    List C = copyList(A);
    printf("List A: \n");
    printListDiags(A);
    printf("List C: \n");
    printListDiags(C);
    append(A, 5);
    List D = concatList(A, C);
    printf("List A: \n");
    printListDiags(A);
    printf("List C: \n");
    printListDiags(C);
    printf("List D: \n");
    printListDiags(D);
    
    //Free lists
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);
    return 0;
}