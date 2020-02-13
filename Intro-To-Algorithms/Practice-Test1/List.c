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
    //if( find(L, k)!=-1 ) {
        //fprintf(stderr, "List Error: insert() called on NULL List reference\n");
        //exit(EXIT_FAILURE);
    //}
    Node new = newNode(k,v);
    new->next = L->head;
    L->head = new;
    (L->numItems)++;
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
        printf("value = %d\n", start->value);
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

// Test Functions -------------------------------------------------------------

// dedup(List L)
// Deletes the subsequent duplicate values from the list.
void dedup(List L) {
    Node current = L->head;
    Node compare = NULL;
    Node prev = NULL;

    while(current!=NULL) {
        compare = current->next;
        prev = current;
        while(compare!=NULL) {
            if(compare->value == current->value) {
                prev->next = compare->next;
                (L->numItems)--;
            }
            compare = compare->next;
            prev = prev->next;
        }
        current = current->next;
    }
}

 //check dedup!!!! ________----------___________----______----___--__---__--


// palindrome()
// checks if the list is a palindrone
int palindrome(List L) {
    Node compare1 = L->head;
    Node compare2 = L->head;
    int length = size(L);
    int i = 1;
    printf("length = %d\n", length);
    while(i < length) {
        compare2 = compare2->next;
        i++;
    }
    length--;
    while(compare1!=NULL) {
        printf("compare1 = %d compare2 = %d\n", compare1->value, compare2->value);
        if(compare1->value!=compare2->value) {
            return 0;
        }
        else {
            compare1 = compare1->next;
            printf("length = %d\n", length);
            compare2 = L->head;
            length--;
            i = 0;
            while(i < length){
                printf("move compare2\n");
                compare2 = compare2->next;
                i++;
            }
            printf("leaving\n");
        }
    }
    return 1;
}

// deletelast()
// Deletes the last occurence of int n and returns a pointer to the deleted Node.
Node deletelast(List L, int n) {
    Node current = L->head;
    Node instance = NULL;
    int count = 1;
    int last = 0;

    while(current!=NULL) {
        if(current->value == n) {
            instance = current;
            last = count-1;
        }
        count++;
        current = current->next;
    }
    count = 1;
    current = L->head;
    while(current!=NULL && count < last) {
        current = current->next;
        count++;
    }
    current->next = current->next->next;
    (L->numItems)--;
    return instance;
}

// rotate()
// Rotates the list by the given int n.
void rotate(List L, int n) {
    printf("\n");
    printf("ROTATE\n");
    Node current = L->head;
    int len = size(L);
    int i = 1, j = 0;
    char* word = "lol";
    int value = 0;

    printf("length = %d n = %d\n", len, n);
    if(n > len) {
        n = n%len;
        printf("modulo\n");
    }
    while(j<n) {
        printf("j = %d n = %d\n", j, n);
        printf("fdfkldf\n");
        current = L->head;
        i = 1;
        while(current!=NULL && i < len-1) {
            current = current->next;
            i++;
        }
        value = current->next->value;
        printf("current value = %d\n", current->value);
        printf("next value = %d\n", value);
        current->next = NULL; // deleting
        printf("finished deleting\n");
        insert(L, word, value); // insert
        j++;

        // Print List
        printf("printing list!\n");
        ListToString(L);
    }
}

// reverse()
// Reverses the first n ints of the List
void reverse(List L, int n) {
    int swap = 0;
    Node compare1 = L->head;
    Node compare2 = L->head;
    int count = 1;
    int i = 1, j = 0;

    if(n > 5){
        n = 5;
    }
    while (compare2->next!=NULL && j < n) {
        compare2 = compare2->next;
        count++;
        j++;
    }
    count--;
    while(compare1!=NULL && i <= n/2) {
        swap = compare1->value;
        compare1->value = compare2->value;
        compare2->value = swap;
        compare1 = compare1->next;
        compare2 = L->head;
        j = 1;
        while(j < count) {
            compare2 = compare2->next;
            j++;
        }
        i++;
    }
}
