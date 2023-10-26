//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
//  FindComponents.c
//  Performs a Depth First Search on inputted Graph/Transposed Graph and prints the strong components to the outfile
//  Uses two command line arguments in form: FindComponents <input file> <output file>
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char * argv[]) {
    FILE *in, *out;

    // check command line for correct number of arguments
    if( argc != 3 ) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if(!in) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if(!out) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // make graph
    int v1, v2;
    fscanf(in, "%d", &v1);
    Graph G = newGraph(v1);

    // make arcs
    while (fscanf(in, "%d %d", &v1, &v2) == 2) {
        if (v1 == 0) { 
            fprintf(out, "Adjacency list representation of G:\n");
            printGraph(out, G);
            break; 
        }
        else {
            addArc(G, v1, v2);
        }
    }

    // initialize stack with vertices
    List S = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }

    // run DFS on G and G^T
    DFS(G, S);
    Graph gT = transpose(G);
    DFS(gT, S);

    // find num of strong components in G
    moveBack(S);
    int num = 0;
    while (index(S) >= 0) {
        if (!getParent(gT, get(S))) {
            num += 1;
        }
        movePrev(S);
    }
    fprintf(out, "\nG contains %d strongly connected components:\n", num);

    // collect components
    List *sccArr = (List*) calloc(num, sizeof(List));
    for (int i = 0; i < num; i++) {
        sccArr[i] = newList();
    }
    moveBack(S);
    int i = 0;
    while (index(S) >= 0) {
        prepend(sccArr[i], get(S));
        if (!getParent(gT, get(S))) {
            i += 1;
        }
        movePrev(S);
    }
        
    // print components
    for (i = 0; i < num; i++) {
        fprintf(out, "Component %d: ", i + 1);
        printList(out, sccArr[i]);
        fprintf(out, "\n");
    }

    // free everything
    for (i = 0; i < num; i++) {
        freeList(&(sccArr[i]));
    }
    free(sccArr);
    sccArr = NULL;
    freeGraph(&G);
    freeGraph(&gT);
    freeList(&S);

    return 0;
}
