//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
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





    return 0;
}
