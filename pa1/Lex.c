//-----------------------------------------------------------------------------
// Lex.c
// Indirectly alphabetizes the lines in a file using a List ADT
// Uses two command line arguments in form: Lex <input file> <output file>
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if(!in){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if(!out){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   int lineCount;
   char line[MAX_LEN];
   char** readLines;
   List L = newList();
   
   while(fgets(line, MAX_LEN, in)) {
      lineCount += 1;
   }
   readLines = (char**) calloc(lineCount, sizeof(char*));
   rewind(in);

   // read each line of input file, then count and print tokens
   lineCount = 0;
   while(fgets(line, MAX_LEN, in))  {
      //printf("read %d %s\n", lineCount, line);
      readLines[lineCount] = (char*) malloc(sizeof(char) * (strlen(line) + 1));
      assert(readLines[lineCount]);
      strcpy(readLines[lineCount], line);
      //printf("%s\n", readLines[lineCount]);

      moveFront(L);
      while (index(L) >= 0) {
         if (strcmp(line, readLines[get(L)]) > 0) {
            moveNext(L);
         }
         else {
            insertBefore(L, lineCount);
            break;
         }
      }
      if (index(L) == -1) {
         append(L, lineCount);
      }
      lineCount += 1;
   }
   //printf("out\n");
   moveFront(L);
   while (index(L) != -1) {
      fprintf(out, "%s", readLines[get(L)]);
      moveNext(L);
   }

   //printf("printed\n");
   
   for (int i = 0; i < lineCount; i++) {
      free(readLines[i]);
   }
   free(readLines);
   freeList(&L);

   //printf("freed\n");
   // close files 
   fclose(in);
   fclose(out);

   //printf("closed\n");

   return(0);
}