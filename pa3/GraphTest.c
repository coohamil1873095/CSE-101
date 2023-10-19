//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
//  GraphTest.c
//  Tests the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main() {
    Graph G = newGraph(10);

    // Test with empty graph
    printf("%d\n", getOrder(G));
    printf("%d\n", getSize(G));
    printf("%d\n", getSource(G));
    printf("%d\n", getParent(G, 1));
    printf("%d\n", getDist(G, 1));

    printGraph(stdout, G);

    // Adding
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 3, 4);
    addEdge(G, 6, 8);
    addEdge(G, 9, 5);

    printGraph(stdout, G);

    // getParent and getDist before BFS
    getParent(G, 1);
    getDist(G, 1);

    // BFS then again
    BFS(G, 1);
    getParent(G, 1);
    getDist(G, 1);

    // getPath
    List L = newList();
    getPath(L, G, 4);
    printList(stdout, L);
    printf("\n");

    clear(L);
    getPath(L, G, 8);
    printList(stdout, L);
    printf("\n");

    // makeNull and freeing
    makeNull(G);
    printGraph(stdout, G);

    freeList(&L);
    freeGraph(&G);

    return 0;
}