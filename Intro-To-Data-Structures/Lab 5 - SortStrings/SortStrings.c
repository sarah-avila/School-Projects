//------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// December 4, 2019
//
// SortStrings.c
// This program converts the sorting algorithm Quicksort so that it operates
// on arrays of strings instead of arrays of integers.
// Compile: $ gcc -std=c99 -Wall -o SortStrings SortStrings.c
// Run: SortStrings in out
//------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

FILE *in, *out;   // input file in and output file out

// printArray()
void printArray(FILE* out, char** A, int n){
   int i;
   for(i=0; i<n; i++){
      fprintf(out, "%s\n", A[i]);
   }
}

// swap()
void swap(char** A, int i, int j){
   char* temp;
   temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}

// Partition()
int Partition(char** A, int p, int r){
   int i, j;
   char* x = A[r];
   i = p-1;
   for(j=p; j<r; j++){
      if( (strcmp(A[j], x) < 0) || (strcmp(A[j], x) == 0) ){
         i++;
         swap(A, i, j);
      }
   }
   swap(A, i+1, r);
   return(i+1);
}

// QuickSort()
void QuickSort(char** A, int p, int r){
   int q;
   if( p<r ){
      q = Partition(A, p, r);
      QuickSort(A, p, q-1);
      QuickSort(A, q+1, r);
   }
}

// main function
int main(int argc, char* argv[]){
  int n = 0;          // number of strings
  char** A;           // array of strings of length n
  int i = 0;          // loop variable


  // check command line for correct number of arguments
  if( argc!= 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // open input file for reading
  in = fopen(argv[1], "r");
  if( in==NULL ){
     printf("Unable to read from file %s\n", argv[1]);
     exit(EXIT_FAILURE);
   }

   // open output file for writing
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // parse n
   fscanf(in, "%d", &n);

   // allocate heap memory
   A = malloc(128);
   assert( A!=NULL );
   for(i = 0; i < n; i++){
     A[i] = malloc(128);
     assert( A[i]!=NULL );
     fscanf(in, "%s", A[i]);
   }

   // sort array
   QuickSort(A, 0, n-1);

   // print array
   printArray(out, A, n);

   // free heap memory
   for(i = 0; i < n; i++){
     free(A[i]);
   }
   free(A);

   // close input and output files
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;

}
