//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA4
//  MatrixTest.c
//  Tests the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, D2, E, F, G, H, I;

    //printf("inserting entries: \n");
   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   //printf("hi1\n");
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   //printf("hi2\n");
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   //printf("hi3\n");
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   //printf("hi4\n");
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   //printf("hi5\n");
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   //printf("hi6\n");
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   //printf("hi7\n");
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   //printf("hi8\n");
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   

   //printf("inserted entries: \n");

    //printf("printing A: \n");
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

    //printf("printing B: \n");
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

    //printf("printing 1.5A: \n");
   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

    //printf("printing A+B: \n");
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   //printf("printing A-B: \n");
   D2 = diff(A, B);
   printf("%d\n", NNZ(D2));
   printMatrix(stdout, D2);
   printf("\n");

    //printf("printing A-A: \n");
   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   // printf("printing A_T: \n");
   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   // printf("printing BB: \n");
   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   // printf("printing copy(A): \n");
   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   

    //printf("printing equalities: \n");
   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

    //printf("printing NNZ(A): \n");
   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

    //printf("freeing: \n");
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&D2);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

8
1: (2, 2.0) (3, 2.0)
2: (1, 4.0) (2, 4.0) (3, 6.0)
3: (1, 6.0) (2, 7.0) (3, 8.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/