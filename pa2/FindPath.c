//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA2
//  FindPath.c
//  Perform a Breadth First Search on inputted source vertices and prints the shortest path to each inputted destination
//  Uses two command line arguments in form: Lex <input file> <output file>
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
        printf("Unable to open file %s for reading\n", argv[1]);
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

    // make edges
    while (fscanf(in, "%d %d", &v1, &v2) == 2) {
        if (v1 == 0) { 
            printGraph(out, G);
            break; 
        }
        else {
            addEdge(G, v1, v2);
        }
    }

    int distance;
    List L = newList();

    // run bfs and print paths
    while (fscanf(in, "%d %d", &v1, &v2) == 2) {
        if (v1 == 0) { break; }
        else {
            BFS(G, v1);
            distance = getDist(G, v2);
            
            fprintf(out, "\n");
            if (distance == INF) {
                fprintf(out, "The distance from %d to %d is infinity\n", v1, v2);
                fprintf(out, "No %d-%d path exists", v1, v2);
            }
            else {
                clear(L);
                getPath(L, G, v2);

                fprintf(out, "The distance from %d to %d is %d\n", v1, v2, distance);
                fprintf(out, "A shortest %d-%d path is: ", v1, v2);
                printList(out, L);
            }
            fprintf(out, "\n");
        }
    }

    // free everything
    freeGraph(&G);
    freeList(&L);

    return 0;
}