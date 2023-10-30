//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA4
//  Sparse.c
//  Print result to output file the Matrix operations A, B, (1.5)A, A + B, A + A, B - A, A - A, A^T, AB, and B^2 given matrices A and B from the input file
//  Uses two command line arguments in form: Sparse <input file> <output file>
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

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


    return 0;
}