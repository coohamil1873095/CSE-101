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

    // get matrix and entry sizes
    int n, a, b;
    if (fscanf(in, "%d %d %d", &n, &a, &b) != 3) {
        fprintf(stderr, "Incorrect number of inputs\n");
        exit(1);
    }
    // skip empty line
    fgetc(in);

    int i, r, c;
    double v;

    // make first matrix
    Matrix A = newMatrix(n);
    // add entries for first matrix
    for (i = 0; i < a; i++) {
        if (fscanf(in, "%d %d %lf", &r, &c, &v) != 3) {
            fprintf(stderr, "Incorrect number of inputs\n");
            exit(1);
        }
        changeEntry(A, r, c, v);
    }
    // skip empty line
    fgetc(in);

    // make second matrix
    Matrix B = newMatrix(n);
    // add entries for second matrix
    for (i = 0; i < b; i++) {
        if (fscanf(in, "%d %d %lf", &r, &c, &v) != 3) {
            fprintf(stderr, "Incorrect number of inputs\n");
            exit(1);
        }
        changeEntry(B, r, c, v);
    }

    // print A
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    // print B
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    // print (1.5)*A
    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");

    // print A+B
    Matrix D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    fprintf(out, "\n");

    // print A+A
    Matrix E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");
    
    // print B-A
    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");
    
    // print A-A
    Matrix G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");

    // print Transpose(A)
    Matrix H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    // print A*B
    Matrix I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");

    // print B*B
    Matrix J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);
    fprintf(out, "\n");
    
    // free everything
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    

    return 0;
}