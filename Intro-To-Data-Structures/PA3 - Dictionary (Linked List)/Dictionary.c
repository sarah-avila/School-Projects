//-----------------------------------------------------------------------------
// Dictionary.c
// Linked List implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"

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
   Node head;         // pointer to first Node in list
   int numItems;      // number of items in this Dictionary
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
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

// findKey()
// returns a reference containing a Node object that has k as its key; otherwise return NULL
// Node findKey(Dictionary D, char* k){
//    Node N = D->head;
//     while( N!=NULL ){
//       if(strcmp(N->key, k) == 0){
//         return N;
//       }
//       N = N->next;
//     }
//     return NULL;
// }

// countChars()
// returns the number of characters in Dictionary D
int countChars(Dictionary D){
  int count = 0;
  Node N = D->head;
  while( N!=NULL ){
    count = count + strlen(N->key);
    count = count + strlen(N->value);
    count = count + 4;
    N = N->next;
  }
  count++;
  return count;
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
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!-NULL);
   D->head = NULL;
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
  return (D->numItems);
}

// lookup()
// If D contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k){
  Node N = D->head;
  while( N!=NULL ){
    if(strcmp(N->key, k) == 0){
      return N->value;
     }
     N = N->next;
  }
  return NULL;
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v){
  if(lookup(D,k)!=NULL){
    fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
    Node N = D->head;
    if( N==NULL ){                   // list was initially empty
      D->head = newNode(k,v);
    }
    else{                            // N = D->head;
      while( N->next!=NULL ){
        N = N->next;
      }
      N->next = newNode(k,v);
    }
    (D->numItems)++;
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k){
  int count = 1;
  Node N = D->head, P = D->head, T = D->head;
  if(lookup(D,k)==NULL){
    fprintf(stderr, "Dictionary Error: delete() called on NULL Dictionary reference\n");
    exit(EXIT_FAILURE);
  }
  while( strcmp(T -> key, k) != 0 ){
    T = T -> next;
    count++;
  }

  if(count == 1){
    D -> head = D -> head -> next;
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
  // if(strcmp(N->key, k) == 0){
  //   D->head = D->head->next;
  // }
  // else{
  //   while(strcmp(N->key, k) != 0){
  //     count++;
  //     N = N->next;
  //   }
  //   int i = 1;
  //   while(i<count - 1){                // go to Node before
  //     P = P->next;
  //     i++;
  //   }
  //   N = P->next;
  //   P->next = N->next;
  // }
  N->next = NULL;
  freeNode(&N);
  (D->numItems)--;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D){
  if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: makeEmpty() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   freeAllNodes(D->head);
   D->head = NULL;
   D->numItems = 0;
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
  Node N = D->head;
  char* str = (char*)malloc(countChars(D) * sizeof(char));
  assert(str!=NULL);
  while(N != NULL){
    strcat(str, N->key);
    strcat(str, " ");
    strcat(str, N->value);
    strcat(str, "\n");
    N = N->next;
  }
  strcat(str, "\0");
  return str;
}
