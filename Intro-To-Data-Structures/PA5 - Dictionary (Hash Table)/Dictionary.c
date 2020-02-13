//-----------------------------------------------------------------------------
// Dictionary.c
// Linked List implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"

const int tableSize = 101;

// Private Types and Functions ------------------------------------------------

// NodeObj type
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj{
   Node* table;       // pointer to an array of Nodes
   int numItems;      // number of items in Dictionary
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->key = k;
   N->value = v;
   N->next = NULL;
   return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// countChars()
// returns the number of characters in Dictionary D
int countChars(Dictionary D){
  int i;
  int count = 0;
  Node N;
  if( size(D)!= 0 ){
    for(i = 0; i < tableSize; i++){
      N = (D->table)[i];
      while( N!=NULL ){
        count = count + strlen(N->key);
        count = count + strlen(N->value);
        count = count + 4;
        N = N->next;
      }
    }
  }
  count++;
  return count;
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
  int sizeInBits = 8*sizeof(unsigned int);
  shift = shift & (sizeInBits - 1);
  if ( shift == 0 )
    return value;
  return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
  unsigned int result = 0xBAE86554;
  while (*input) {
    result ^= *input++;
    result = rotate_left(result, 5);
  }
  return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
  return pre_hash(key)%tableSize;
}

// freeAllNodes()
// uses recursion to free all the Nodes in list headed by N
void freeAllNodes(Node N){
   if( N!=NULL ){
      freeAllNodes(N->next);
      freeNode(&N);
   }
}

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary ADT
Dictionary newDictionary(){
   int i;
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->table = calloc(tableSize, sizeof(Node));
   assert(D!=NULL);
   for(i = 0; i < tableSize; i++){
     (D->table)[i] = NULL;
   }
   D->numItems = 0;
   return D;
}

// freeDictionary()
// Destructor for the Dictionary ADT
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}

// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
  if(D==NULL){
    fprintf(stderr, "Dictionary Error: size() called on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
  return D->numItems;
}

// lookup()
// If D contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k){
  int index = hash(k);
  if( D->numItems!= 0 ){
    Node N = (D -> table)[index];
    while( N!=NULL ){
        if( strcmp(N -> key, k) == 0 ){
          return N -> value;
        }
        N = N -> next;
      }
    }
    return NULL;
  }


// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v){
  int index = hash(k);
  if(lookup(D,k)!=NULL){
    fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
  Node N = newNode(k,v);
  N->next = (D->table)[index];
  (D->table)[index] = N;
  D->numItems++;
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k){
  int count = 1;
  int index  = hash(k);
  Node N = (D->table)[index], P = (D->table)[index], T = (D->table)[index];
  if( lookup(D,k)==NULL ){
    fprintf(stderr, "Dictionary Error: delete() called on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }

  while( strcmp(T -> key, k) != 0 ){
    T = T -> next;
    count++;
  }

  if(count == 1){
    (D->table)[index] = (D->table)[index] -> next;
  }
  else {
    int i = 1;
    while(i < count-1){
      P = P -> next;
      i++;
    }

    N = P -> next;
    P -> next = N -> next;
  }
  N -> next = NULL;
  freeNode(&N);
  D->numItems--;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D){
  int i;
  if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: makeEmpty() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   if(size(D) != 0){
     for(i = 0; i < tableSize; i++){
       freeAllNodes((D->table)[i]);
     }
     D->numItems = 0;
   }
   free(D->table);
   D->table = NULL;
}

// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs
// occur in the same order they were inserted into D. The function returns a
// pointer to a char array, allocated from heap memory, containing the text
// representation described above, followed by a terminating null '\0' char.
// It is the responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D){
  int i;
  Node N;
  char* str = calloc(countChars(D), sizeof(char));
  assert( str!=NULL );
  if(size(D) != 0){
    for(i = 0; i < tableSize; i++){
      N = (D->table)[i];
      while(N != NULL){
        strcat(str, N->key);
        strcat(str, " ");
        strcat(str, N->value);
        strcat(str, "\n");
        N = N->next;
      }
    }
  }
  strcat(str, "\0");
  return str;
}
