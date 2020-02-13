//-----------------------------------------------------------------------------
// List.c
// Linked List implementation for the List ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"

// Private Types and Functions ------------------------------------------------

// NodeObj Type
typedef struct NodeObj{
    char key[40];
    int value;
    struct NodeObj* next;
} NodeObj;

// ListObj Type
typedef struct ListObj{
    Node head;              // pointer to the first Node in a List
    int numItems;           // number of (key, value) pairs in the List
} ListObj;

// newNode()
// Constructor for the Node type.
Node newNode(char* k, int v) {
    Node N = malloc(sizeof(NodeObj));
    strcpy(N->key,k);
    N->value = v;
    N->next = NULL;
    return N;
}

// freeNode()
// Destructor for the Node type.
void freeNode(Node* pL) {
    if( pL!=NULL && *pL!=NULL ) {
        free(*pL);
        *pL = NULL;
    }
}

// freeAllNodes()
// Frees all the Nodes in the List headed by N.
void freeAllNodes(Node N) {
    if( N!=NULL) {
        freeAllNodes(N->next);
        freeNode(&N);
    }
}

// Constructors-Destructors ---------------------------------------------------

// newList()
// Constructor for the List ADT.
List newList() {
    List L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->numItems = 0;
    return L;
}

// freeList()
// Destructor for the List ADT.
void freeList(List* pL) {
    if ( pL!=NULL && *pL!=NULL ) {
        makeEmpty(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// ADT Operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in the List headed by start.
int size(List L) {
    if( L==NULL ) {
        fprintf(stderr, "List Error: size() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return (L->numItems);
}

// find()
// If L contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
int find(List L, char* k) {
    Node start = L->head;
    while( start!=NULL ) {
        if( (strcmp(start->key, k))==0 ) {
            return start->value;
        }
        start = start->next;
    }
    return -1;
}

// traverse()
// Traverses through the List for a given n number of times.
char* traverse(List L, int n) {
    Node current = L->head;
    int i=0;
    //char* answerKey = malloc(sizeof(char));
    while(current!=NULL && i<n){
        current = current->next;
        i++;
    }
    return current->key;
}


// insert()
// Insert the (key, value) pair at the head of List L.
// Pre: find(start, k)==NULL
void insert(List L, char* k, int v) {
    if( find(L, k)!=-1 ) {
        fprintf(stderr, "List Error: insert() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node new = newNode(k,v);
    new->next = L->head;
    L->head = new;
    L->numItems++;
}


// updateValue()
// Updates the frequency of a word when it is found again.
void updateValue(List L, char* k) {
    Node start = L->head;
    while( start!=NULL ) {
        if( strcmp(start->key,k)==0 ) {
            (start->value)++;
            return;
        }
        start = start->next;
    }
}

// makeEmpty()
// Reset L to the empty state.
void makeEmpty(List L) {
    if( L==NULL ) {
        fprintf(stderr, "List Error: makeEmpty() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    freeAllNodes(L->head);
    L->head=NULL;
    L->numItems=0;
}

// Other Operations -----------------------------------------------------------

// ListToString()
// Prints out the List L.
void ListToString(List L) {
    Node start = L->head;
    while( start!=NULL ){
        printf("key = %s value = %d\n", start->key, start->value);
        start = start->next;
    }
    printf("NULL\n");
}

// insertionSort()
// Sorts the given List using the Insertion Sort method
void insertionSort(List L) {
    char tempC[50]; //tempfreq2
    int tempV = 0;
    char swapC[50];
    int swapV = 0;
    Node start = L->head;
    if( start!=NULL && start->next!=NULL ) {
        Node current = L->head->next; //t1
            while( current!=NULL ) {
                int readyToSwap = 0;
                Node loop = L->head; //t2
                // Store current (key, value) in swap Node
                strcpy(swapC, current->key);
                swapV = current->value;
                    while( loop!=current ) {
                        if( (loop->value <= current->value) && (readyToSwap == 0) ) {
                            if( loop->value == current->value && strcmp(loop->key, current->key) < 0 ) {
                                loop = loop->next;
                                continue;
                            }
                            // Store loop in swap Node
                            strcpy(swapC, loop->key);
                            swapV = loop->value;
                            strcpy(loop->key, current->key);
                            loop->value = current->value;
                            readyToSwap = 1;
                            loop = loop->next;
                        }
                        else {
                            if( readyToSwap==1 ) {
                                // Shift all Node values to the right
                                strcpy(tempC, swapC);
                                tempV = swapV;
                                strcpy(swapC, loop->key);
                                swapV = loop->value;
                                strcpy(loop->key, tempC);
                                loop->value = tempV;
                            }
                            loop = loop->next;
                        }
                    }
                    // Swap loop and current values to finish Sort
                    strcpy(loop->key, swapC);
                    loop->value = swapV;
                    current = current->next;

            }
    }

}
