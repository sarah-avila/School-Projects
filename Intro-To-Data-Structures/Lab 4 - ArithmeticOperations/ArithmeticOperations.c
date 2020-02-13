//------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// November 18, 2019
//
// ArithmeticOperations.c
// This program uses function pointers to evaluate arithmetic expressions
// Compile: $ gcc -std=c99 -Wall -o ArithmeticOperations ArithmeticOperations.c
// Run: ArithmeticOperations
//------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

// Define fptr_t type
typedef int (*fptr_t)(int, int);

int sum(int x, int y){
  return x + y;
}

int diff(int x, int y){
  return x - y;
}

int prod(int x, int y){
  return x * y;
}

int quot(int x, int y){
  return x / y;
}

int rem(int x, int y){
  return x % y;
}

int apply(fptr_t fp, int x, int y){
  return fp(x,y);
}

int compute(fptr_t fcn[5], int* A, int* idx, int n){
  int i, j = 0;
  int temp;
  int total = 0;
  for(i = 0; i < n+1; i++){
    temp = idx[j];
    if( i == 0 ){  // first case
      total = apply(fcn[temp], A[i], A[i+1]);
      i++;
    }
    else{
      total = apply(fcn[temp], total, A[i]);
    }
    j++;
  }
  return total;
}

int main(int argc, char** argv){

  FILE* in = fopen(argv[1], "r");        // input file
  fptr_t op[]  = {sum, diff, prod, quot, rem};
  //int A[]; //{3, 2, 5, 4, 6, 7, 9, 2, 8};
  //int opCode[]; //{0, 2, 1, 4, 2, 2, 3, 1};
  int i, n;
  int* p1;
  int* p2;
  int total = 0;

  // check for input file
  if( in == NULL){
    printf("ERROR: input file called on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  // initialize A and opCode arrays
  fscanf(in, "%d", &n);
  int A[n];
  int opCode[n+1];
  p1 = (int*)malloc(n*sizeof(int));
  p2 = (int*)malloc((n+1)*sizeof(int));
  assert(p1!=NULL && p2!=NULL);
  for(i = 0; i < n; i++){
    fscanf(in, "%d", &opCode[i]);
  }
  for(i = 0; i < n+1; i++){
    fscanf(in, "%d", &A[i]);
  }

  // compute total
  total = compute(op, A, opCode, n);
  printf("%d\n", total);

  // free heap memory
  free(p1);
  free(p2);

  // close input file
  fclose(in);

  return EXIT_SUCCESS;
}
