//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA4
//  Matrix.h
//  Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

// struct --------------------------------------------------------------------

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

// private MatrixObj type 
typedef struct MatrixObj {
    List* entries;
    int size;
    int nonZeroes;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Entry object.
Entry newEntry(int col, double val) {
    Entry E = (EntryObj*) malloc(sizeof(EntryObj));
    assert(E);
    E->column = col;
    E->value = val;
    return E;
}

// Frees heap memory associated with *pE, sets *pE to NULL.
void freeEntry(Entry* pE) {
    if (pE && *pE) {
        free(*pE);
        *pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = (MatrixObj*) malloc(sizeof(MatrixObj));
    assert(M);
    M->entries = (List*) calloc(n + 1, sizeof(List));
    for (int i = 1; i <= n; i++) {
        M->entries[i] = newList();
    }
    M->size = n;
    M->nonZeroes = 0;
    return M;
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM && *pM) {
        for (int i = 1; i <= (*pM)->size; i++) {
            moveFront((*pM)->entries[i]);
            while (index((*pM)->entries[i]) >= 0) {
                Entry E = (Entry)get((*pM)->entries[i]);
                freeEntry(&E);
                moveNext((*pM)->entries[i]);
            }
            freeList(&((*pM)->entries[i]));
        }
        free((*pM)->entries);
        free(*pM);
        *pM = NULL;
    }
}

// Error functions

void checkMatrixExist(Matrix M, char* function) {
    if(!M){
        fprintf(stderr, "Matrix Error: calling %s() on NULL Matrix reference\n", function);
        exit(EXIT_FAILURE);
    }
}
void checkMatrixSize(Matrix A, Matrix B, char* function) {
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling %s() on Matrices of differing sizes\n", function);
        exit(EXIT_FAILURE);
    }
}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    checkMatrixExist(M, "size");
    return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    checkMatrixExist(M, "NNZ");
    return M->nonZeroes;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if(!A || !B){
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        return 0;
    }
    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0 && length(B->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        moveFront(B->entries[i]);
        while (index(A->entries[i]) >= 0 && index(B->entries[i]) >= 0) {
            Entry e_A = (Entry)get(A->entries[i]);
            Entry e_B = (Entry)get(B->entries[i]);
            if (e_A->column != e_B->column || e_A->value != e_B->value) {
                return 0;
            }
            moveNext(A->entries[i]);
            moveNext(B->entries[i]);
        }
        if (index(A->entries[i]) >= 0 || index(B->entries[i]) >= 0) {
            return 0;
        }
    }
    return 1;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    checkMatrixExist(M, "makeZero");
    for (int i = 1; i <= M->size; i++) {
        moveFront(M->entries[i]);
        while (index(M->entries[i]) >= 0) {
            Entry E = (Entry)get(M->entries[i]);
            freeEntry(&E);
            moveNext(M->entries[i]);
        }
        clear(M->entries[i]);
    }
    M->nonZeroes = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    checkMatrixExist(M, "changeEntry");
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        printf("Matrix Error: calling changeEntry() with invalid indices\n");
        exit(EXIT_FAILURE);
    }
    moveFront(M->entries[i]);
    while (index(M->entries[i]) >= 0) {
        Entry E = (Entry)get(M->entries[i]);
        // at correct entry
        if (E->column == j) {
            if (x != 0) {
                E->value = x;
            }
            else if (x == 0) {
                // delete from list
                freeEntry(&E);
                delete(M->entries[i]);
                M->nonZeroes -= 1;
            }
            return;
        }
        // past desired column
        else if (E->column > j) {
            if (x != 0) {
                insertBefore(M->entries[i], newEntry(j, x));
                M->nonZeroes += 1;
            }
            return;
        }
        moveNext(M->entries[i]);
    }
    // no entry exists past desired column
    if (index(M->entries[i]) == -1) {
        if (x != 0) {
            append(M->entries[i], newEntry(j, x));
            M->nonZeroes += 1;
        }
    }
}

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    checkMatrixExist(A, "copy");
    Matrix B = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        while (index(A->entries[i]) >= 0) {
            Entry E = (Entry)get(A->entries[i]);
            append(B->entries[i], newEntry(E->column, E->value));
            moveNext(A->entries[i]);
        }
    }
    B->nonZeroes = A->nonZeroes;
    return B;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    checkMatrixExist(A, "transpose");
    Matrix B = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        while (index(A->entries[i]) >= 0) {
            Entry E = (Entry)get(A->entries[i]);
            append(B->entries[E->column], newEntry(i, E->value));
            moveNext(A->entries[i]);
        }
    }
    B->nonZeroes = A->nonZeroes;
    return B;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    checkMatrixExist(A, "scalarMult");
    Matrix B = newMatrix(A->size);
    if (x == 0) {
        return B;
    }
    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        while (index(A->entries[i]) >= 0) {
            Entry E = (Entry)get(A->entries[i]);
            append(B->entries[i], newEntry(E->column, E->value * x));
            moveNext(A->entries[i]);
        }
    }
    B->nonZeroes = A->nonZeroes;
    return B;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    checkMatrixExist(A, "sum");
    checkMatrixExist(B, "sum");
    checkMatrixSize(A, B, "sum");

    if (equals(A, B)) {
        return scalarMult(2, A);
    }
    Matrix C = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0 && length(B->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        moveFront(B->entries[i]);
        Entry e_A, e_B;
        while (index(A->entries[i]) >= 0 && index(B->entries[i]) >= 0) {
            e_A = (Entry)get(A->entries[i]);
            e_B = (Entry)get(B->entries[i]);

            // Check if addition needs to be done
            if (e_A->column == e_B->column) {
                if (e_A->value + e_B->value != 0) {
                    append(C->entries[i], newEntry(e_A->column, e_A->value + e_B->value));
                    C->nonZeroes += 1;
                }
                moveNext(A->entries[i]);
                moveNext(B->entries[i]);
            }
            // A_ij + 0
            else if (e_A->column < e_B->column) {
                append(C->entries[i], newEntry(e_A->column, e_A->value));
                moveNext(A->entries[i]);
                C->nonZeroes += 1;
            }
            // 0 + B_ij
            else if (e_A->column > e_B->column) {
                append(C->entries[i], newEntry(e_B->column, e_B->value));
                moveNext(B->entries[i]);
                C->nonZeroes += 1;
            }
        }
        // Adding leftover values after a list ends
        while (index(A->entries[i]) >= 0) {
            e_A = (Entry)get(A->entries[i]);
            append(C->entries[i], newEntry(e_A->column, e_A->value));
            moveNext(A->entries[i]);
            C->nonZeroes += 1;
        }
        while (index(B->entries[i]) >= 0) {
            e_B = (Entry)get(B->entries[i]);
            append(C->entries[i], newEntry(e_B->column, e_B->value));
            moveNext(B->entries[i]);
            C->nonZeroes += 1;
        }
    }
    return C;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    checkMatrixExist(A, "diff");
    checkMatrixExist(B, "diff");
    checkMatrixSize(A, B, "diff");

    Matrix C = newMatrix(A->size);
    if (equals(A, B)) {
        return C;
    }

    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0 && length(B->entries[i]) == 0) {
            continue;
        }
        moveFront(A->entries[i]);
        moveFront(B->entries[i]);
        Entry e_A, e_B;
        while (index(A->entries[i]) >= 0 && index(B->entries[i]) >= 0) {
            e_A = (Entry)get(A->entries[i]);
            e_B = (Entry)get(B->entries[i]);
            
            // Check if subtraction needs to be done
            if (e_A->column == e_B->column) {
                if (e_A->value - e_B->value != 0) {
                    append(C->entries[i], newEntry(e_A->column, e_A->value - e_B->value));
                    C->nonZeroes += 1;
                }
                moveNext(A->entries[i]);
                moveNext(B->entries[i]);
            }
            // A_ij - 0
            else if (e_A->column < e_B->column) {
                append(C->entries[i], newEntry(e_A->column, e_A->value));
                moveNext(A->entries[i]);
                C->nonZeroes += 1;
            }
            // 0 - B_ij
            else if (e_A->column > e_B->column) {
                append(C->entries[i], newEntry(e_B->column, e_B->value * -1));
                moveNext(B->entries[i]);
                C->nonZeroes += 1;
            }
        }
        // Adding leftover values after a list ends
        while (index(A->entries[i]) >= 0) {
            e_A = (Entry)get(A->entries[i]);
            append(C->entries[i], newEntry(e_A->column, e_A->value));
            moveNext(A->entries[i]);
            C->nonZeroes += 1;
        }
        while (index(B->entries[i]) >= 0) {
            e_B = (Entry)get(B->entries[i]);
            append(C->entries[i], newEntry(e_B->column, e_B->value * -1));
            moveNext(B->entries[i]);
            C->nonZeroes += 1;
        }
    }
    return C;
}

double vectorDot(List P, List Q) {
    double ret = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        Entry e_P = (Entry)get(P);
        Entry e_Q = (Entry)get(Q);
        if (e_P->column == e_Q->column) {
            ret += (e_P->value * e_Q->value);
            moveNext(P);
            moveNext(Q);
        }
        else if (e_P->column > e_Q->column) { moveNext(Q); }
        else if (e_P->column < e_Q->column) { moveNext(P); }
    }
    return ret;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    checkMatrixExist(A, "product");
    checkMatrixExist(B, "product");
    checkMatrixSize(A, B, "product");
    Matrix C = newMatrix(A->size);
    Matrix t_B = transpose(B);
    for (int i = 1; i <= A->size; i++) {
        if (length(A->entries[i]) == 0) {
            continue;
        }
        for (int j = 1; j <= t_B->size; j++) {
            if (length(t_B->entries[j]) == 0) {
                continue;
            }
            double sum = vectorDot(A->entries[i], t_B->entries[j]);
            if (sum != 0) {
                append(C->entries[i], newEntry(j, sum));
                C->nonZeroes += 1;
            }
        }
    }
    freeMatrix(&t_B);
    return C;
}

// Other operations -----------------------------------------------------------

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    checkMatrixExist(M, "printMatrix");
    for (int i = 1; i <= M->size; i++) {
        if (length(M->entries[i]) != 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->entries[i]);
            while (index(M->entries[i]) >= 0) {
                Entry E = (Entry)get(M->entries[i]);
                fprintf(out, "(%d, %0.1f) ", E->column, E->value);
                moveNext(M->entries[i]);
            }
            fprintf(out, "\n");
        }
    }
}