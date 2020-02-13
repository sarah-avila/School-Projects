//------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// November 25, 2019
//
// IntegerQueueTest.c
// An IntegerQueue ADT based on a linked list data structure
// Compile: $ gcc -std=c99 -Wall -o IntegerQueueTest IntegerQueueTest.c
// Run: IntegerQueueTest
//------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"IntegerQueue.h"

int main(){

   int i, j;
   char* str1;
   char* str2;

   IntegerQueue A = newIntegerQueue();
   IntegerQueue B = newIntegerQueue();

   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   enqueue(A, 1);
   enqueue(A, 2);
   enqueue(A, 3);
   enqueue(A, 4);
   enqueue(A, 5);

   printf("%s\n", isEmpty(A)?"true":"false");

   str1 = IntegerQueueToString(A);
   printf("%s\n", str1);
   free(str1);

   printf("%d\n", peek(A));
   dequeue(A);
   dequeue(A);
   dequeue(A);
   printf("%d\n", peek(A));

   str1 = IntegerQueueToString(A);
   printf("%s\n", str1);
   free(str1);

   enqueue(B, 4);
   enqueue(B, 5);

   str2 = IntegerQueueToString(B);
   printf("%s\n", str2);
   free(str2);
   printf("%s\n", equals(A, B)?"true":"false");

   enqueue(A, 6);
   enqueue(B, 7);

   str1 = IntegerQueueToString(A);
   printf("%s\n", str1);
   free(str1);

   str2 = IntegerQueueToString(B);
   printf("%s\n", str2);
   free(str2);

   printf("%s\n", equals(A, B)?"true":"false");

   dequeueAll(A);
   dequeueAll(B);
   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   freeIntegerQueue(&A);
   freeIntegerQueue(&B);

   A = newIntegerQueue();
   B = newIntegerQueue();

   for(i=0; i<10; i++){
      enqueue(A, i);
   }

   str1 = IntegerQueueToString(A);
   str2 = IntegerQueueToString(B);
   printf("A: %s\n", str1);
   printf("B: %s\n", str2);
   free(str1);
   free(str2);

   while( !isEmpty(A) ){
      j = dequeue(A);
      enqueue(B, j);
      if( j%3==0 ){
         j = dequeue(B);
         enqueue(A, j);
      }
      str1 = IntegerQueueToString(A);
      str2 = IntegerQueueToString(B);
      printf("A: %s\n", str1);
      printf("B: %s\n", str2);
      free(str1);
      free(str2);
   }

   freeIntegerQueue(&A);
   freeIntegerQueue(&B);

   return EXIT_SUCCESS;
}

/* Output of this program: ****************************************************
true
true
false
1 2 3 4 5
1
4
4 5
4 5
true
4 5 6
4 5 7
false
true
true
A: 0 1 2 3 4 5 6 7 8 9
B:
A: 1 2 3 4 5 6 7 8 9 0
B:
A: 2 3 4 5 6 7 8 9 0
B: 1
A: 3 4 5 6 7 8 9 0
B: 1 2
A: 4 5 6 7 8 9 0 1
B: 2 3
A: 5 6 7 8 9 0 1
B: 2 3 4
A: 6 7 8 9 0 1
B: 2 3 4 5
A: 7 8 9 0 1 2
B: 3 4 5 6
A: 8 9 0 1 2
B: 3 4 5 6 7
A: 9 0 1 2
B: 3 4 5 6 7 8
A: 0 1 2 3
B: 4 5 6 7 8 9
A: 1 2 3 4
B: 5 6 7 8 9 0
A: 2 3 4
B: 5 6 7 8 9 0 1
A: 3 4
B: 5 6 7 8 9 0 1 2
A: 4 5
B: 6 7 8 9 0 1 2 3
A: 5
B: 6 7 8 9 0 1 2 3 4
A:
B: 6 7 8 9 0 1 2 3 4 5
******************************************************************************/
