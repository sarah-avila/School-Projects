//-----------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// November 1, 2019
//
// IntegerStack.c
// Array based implementation of Integer Stack ADT in C (with array doubling)
// Compile: $ gcc -std=c99 -Wall -o IntegerStack IntegerStack.c
// Run: IntegerStack
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"IntegerStack.h"

#define InitialSize 1

// Private Types and Functions ------------------------------------------------

// IntegerStackObj
typedef struct IntegerStackObj{
   int* item;           // array of IntegerStack items
   int numItems;        // number of items in this IntegerStack
   int arrayLength;     // current length of array
} IntegerStackObj;

// doubleItemArray
// Doubles the size of the array S->item.
void doubleItemArray(IntegerStack S) {
   int i;
   int* newArray;
   int* oldArray = S->item;
   S->arrayLength *= 2;
   newArray = calloc(S->arrayLength, sizeof(int));
   for( i=0; i<(S->numItems); i++){
      newArray[i] = oldArray[i];
   }
   S->item = newArray;
   free(oldArray);
}

// arrayIndex()
// Transforms an IntegerStack index to an Array index
int arrayIndex(int stackIndex){
   return stackIndex-1;
}

// Constructors - Destructors -------------------------------------------------

// newIntegerStack()
// Constructor for the IntegerStack ADT
IntegerStack newIntegerStack(){
   IntegerStack S = malloc(sizeof(IntegerStackObj));
   S->item = calloc(InitialSize, sizeof(int));
   S->numItems = 0;
   S->arrayLength = InitialSize;
   return S;
}

// freeIntegerStack()
// Destructor for the IntegerStack ADT
void freeIntegerStack(IntegerStack* pS){
   if( pS!=NULL && *pS!=NULL ){
      free((*pS)->item);
      free(*pS);
      *pS = NULL;
      }
}


// ADT Operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Stack S is empty, 0 (false) otherwise.
int isEmpty(IntegerStack S){
 if( S==NULL ){
    fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
 }

 return (S->numItems == 0);
}

// push()
// Inserts x on top of stack S.
void push(IntegerStack S, int x){
 if( S==NULL ){
    fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
 }

 // increase array length if necessary
 if( (S->numItems)==(S->arrayLength) ){
    doubleItemArray(S);
 }

 S->item[S->numItems] = x;
 S->numItems++;
}

// pop()
// Deletes and returns the integer at the top of stack S.
// Pre: !isEmpty()
int pop(IntegerStack S){
 int x;
 if( S==NULL ){
    fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
 }
 if(isEmpty(S)){
    fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
    exit(EXIT_FAILURE);
 }

 x = S->item[arrayIndex(S->numItems)];
 S->numItems--;
 return x;
}

int peek(IntegerStack S){
   int x;
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(S)){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   x = S->item[arrayIndex(S->numItems)];
   return x;
}

// popAll()
// Resets S to the empty state.
void popAll(IntegerStack S){
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   S->numItems = 0;
}


// Other Operations -----------------------------------------------------------

// printintegerStack()
// Prints a space separated list of items in S to file stream pointed to be out.
void printIntegerStack(FILE* our, IntegerStack S){
   int i;
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   for( i=1; i<=(S->numItems); i++){
      printf("%d ", S->item[arrayIndex(i)]);
   }
   printf("\n");
}

// equals()
// Returns 1 (true) if S and R are matching sequences of integers, 0 (false) otherwise
int equals(IntegerStack S, IntegerStack R){
   int i, eq;
   if( S==NULL || R==NULL ){
      fprintf(stderr, "IntegerList Error: equals() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (S->numItems)==(R->numItems) );
   for( i=1; eq && i<=(S->numItems);i++){
      eq = ( (S->item[arrayIndex(i)])==(R->item[arrayIndex(i)]) );
   }

   return eq;
}

                                                              1,1           Top
