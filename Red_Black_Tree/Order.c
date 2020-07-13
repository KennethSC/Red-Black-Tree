#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "RB_Tree.h"

#define MAX_LEN 500

int main( int argc, char* argv[])
{
   FILE* in;
   FILE* out;
   int i;
   int k;
   int l;
   int numLines = 0;
   int n;
   char lines[MAX_LEN];
   char** strArr;


   // check command line for correct number of arguments
   if( argc != 3 )
   {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");


   if( in == NULL )
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   if( out == NULL )
   {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(EXIT_FAILURE);
   }


   // gets number of lines in file    
   while( fgets(lines, MAX_LEN, in) != NULL)
   {
      numLines++;
   }


   // closes in file
   fclose(in);

      
   // reopens in  file to start reading from begining again
   in = fopen(argv[1], "r");
     
   if( in == NULL )
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(EXIT_FAILURE);
   }


   // allocate memory for array of strings
   strArr = calloc(numLines, sizeof(char*));
   assert(strArr != NULL);


   // allocate memory for each line of file of length MAX_LEN
   for(i = 0; i < numLines; i++)
   {
      strArr[i] = calloc(MAX_LEN, sizeof(char));
      assert(strArr[i] != NULL);
   }


   // copy each line of file into its own indice.
   for(n = 0; n < numLines; n++)
   {
      fgets(strArr[n], MAX_LEN, in);
   }



   // Create newTree() D
   Tree D = newTree(0);



   // Insert each word into the 
   // Tree in Lexicographic
   // order. Insert already does that
   // by using KEY_CMP (strcmp())
   for(k = 0; k < numLines; k++)
   {
      insert(D, strArr[k], NULL);
   }



   // Printing out the contents of
   // Tree D in a preOrder
   // tree walk
   printTree(out, D, "pre");


   // Printing out the contents of
   // Tree D in an inOrder
   // tree walk
   printTree(out, D, "in");


   // Printing out the contents of
   // Tree D in a postOrder
   // tree walk
   printTree(out, D, "post");



   
   // deallocates memory for each line
   for(l = 0; l < numLines; l++)
   {
      free(strArr[l]);
      strArr[l] = NULL;
   }
     
 
   // deallocates memory for string array
   free(strArr);
   strArr = NULL;


   freeTree(&D);
     
   // close files
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;

}











