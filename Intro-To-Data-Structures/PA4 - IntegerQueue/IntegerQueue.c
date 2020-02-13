//------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// November 25, 2019
//
// IntegerQueue.c
// An IntegerQueue ADT based on a linked list data structure
// Compile: $ gcc -std=c99 -Wall -o IntegerQueue IntegerQueue.c
// Run: IntegerQueue
//------------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"IntegerQueue.h"

// Private Types and Functions -------------------------------------------------

// NodeObj type
typedef struct NodeObj{
  int item;
  struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

typedef struct IntegerQueueObj{
  Node head;     //points to the first Node in the list
  Node tail;     //points to the last Node in the list
  int numItems; // number of items in the IntegerQueue
} IntegerQueueObj;

// newNode()
// Constructor for Node type
Node newNode(int x) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->item = x;
   N->next = NULL;
   return N;
}

//freeNode()
// Destructor for Node type
void freeNode(Node* pN){
  if(pN!=NULL && *pN!=NULL){
    free(*pN);
    *pN = NULL;
  }
}

//freeAllNodes()
// uses recursion to free all the Nodes in the list with head N
void freeAllNodes(Node N){
  if(N!=NULL){
    freeAllNodes(N->next);
    free(N);
  }
}

// countChars()
// returns the number of integers in IntegerQueue Q
int countDigits(IntegerQueue Q){
  int i, count = 0;
  Node N = Q->head;
  while( N!=NULL ){
    i = (N->item);
    while(i!=0){
      i = i/10;
      count++;
    }
    count++;
    N = N->next;
  }
  count++;
  return count;
}


// Constructors-Destructors ----------------------------------------------------

// newIntegerQueue()
// IntegerQueue Constructor
IntegerQueue newIntegerQueue(){
  IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
  assert(Q!=NULL);
  Q->head = NULL;
  Q->tail = NULL;
  Q-> numItems = 0;
  return Q;
}

// freeIntegerQueue()
// IntegerQueue Destructor
void freeIntegerQueue(IntegerQueue* pQ){
  if( pQ!=NULL && *pQ!=NULL ){
    free(*pQ);
    *pQ = NULL;
  }
}

// ADT Operations --------------------------------------------------------------

//isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise
int isEmpty(IntegerQueue Q){
  if(Q == NULL){
    fprintf(stderr, "ERROR: isEmpty() called on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  return (Q->numItems == 0);
}

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q){
  if(Q == NULL){
    fprintf(stderr, "ERROR: length() called on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  return Q->numItems;
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
  Node N = newNode(x);
  if(Q == NULL){
    fprintf(stderr, "ERROR: enqueue() called on NULL reference\n");
    exit(EXIT_FAILURE);
  }

  if(Q->head == NULL){
    Q->head = Q->tail = N;
  }
  else{
    Q->tail->next = N;
    Q->tail = N;
  }
  Q->numItems++;
  }


// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q){
  int x;
  Node N = Q->head;
  if(Q->head == NULL){
    fprintf(stderr, "Error: dequeue() called on NULL reference\n");
    exit(EXIT_FAILURE);
    }
  if(isEmpty(Q)){
    fprintf(stderr, "Error: dequeue() called on empty list\n");
    exit(EXIT_FAILURE);
  }

  x = N->item;
  if(Q->head == Q->tail){
    Q->head = Q->tail = NULL;
  }
  else{
    Q->head = N->next;
  }
  freeNode(&N);
  Q->numItems--;
  return x;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q){
  if(Q->head == NULL){
    fprintf(stderr, "Error: peek() called on NULL reference\n");
    exit(EXIT_FAILURE);
    }
  if(isEmpty(Q)){
    fprintf(stderr, "Error: peek() called on empty list\n");
    exit(EXIT_FAILURE);
  }

  return Q->head->item;
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q){
  if(Q->head == NULL){
    fprintf(stderr, "Error: dequeueAll() called on NULL reference\n");
    exit(EXIT_FAILURE);
    }

  freeAllNodes(Q->head);
  Q->head = NULL;
  Q->tail = NULL;
  Q->numItems = 0;
}

// Other Operations ------------------------------------------------------------

// printIntegerQueue()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a
// char array, allocated from heap memory, containing the integer sequence
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated
// by a NUL '\n' character. It is the responsibility of the calling function to
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q){
  Node N = Q->head;
  int length;
  char* intToStr = malloc(sizeof(int));
  char* str = malloc(countDigits(Q) * sizeof(int));
  assert(str!=NULL);
  while(N != NULL){
    length = snprintf(NULL, 0, "%d", N->item);
    intToStr = malloc(length + 1);
    snprintf(intToStr, length+1, "%d", N->item);
    strcat(str, intToStr);
    strcat(str, " ");
    N = N->next;
  }
  strcat(str, "\0");
  free(intToStr);
  return str;
}

// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0)
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R){
  Node N = Q->head;
  Node M = R->head;
  int eq = 0;
  if( Q==NULL || R==NULL ){
     fprintf(stderr, "Error: equals() called on NULL reference");
     exit(EXIT_FAILURE);
  }


  eq = ( (Q->numItems)==(R->numItems) );
  while(N!=NULL && M!=NULL){
     eq = ( (N->item)==(M->item) );
     N=N->next;
     M=M->next;
  }
  return eq;
}
