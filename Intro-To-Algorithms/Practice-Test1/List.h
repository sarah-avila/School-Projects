//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_

// Exported type --------------------------------------------------------------

// Type Definitions
typedef struct NodeObj* Node;
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Constructor for the List ADT.
List newList();

// freeList()
// Destructor for the List ADT.
void freeList(List* pL);

// ADT Operations -------------------------------------------------------------

// getKey()
// Returns the key of the passed Node.
int getKey(List L);

// getValue()
// Returns the value of the passed Node.
char* getValue(List L);

// size()
// Return the number of (key, value) pairs in List L.
int size(List L);

// find()
// If L contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
int find(List L, char* k);

// traverse()
// Traverses through the List for a given n number of times.
char* traverse(List L, int n);

// insert()
// Insert the pair (k,v) into L.
void insert(List L, char* k, int v);

// updateValue()
// Updates the frequency of a word when it is found again.
void updateValue(List L, char* k);

// makeEmpty()
// Reset L to the empty state.
void makeEmpty(List L);

// Other Operations -----------------------------------------------------------

// ListToString()
// Prints out the List L.
void ListToString(List L);

// insertionSort()
// Sorts the given List using the Insertion Sort Method
void insertionSort(List L);

// Test Functions -------------------------------------------------------------

// dedup()
// Deletes the subsequent duplicate values from the list.
void dedup(List L);

// palindrome()
// checks if the list is a palindrone
int palindrome(List L);

// deletelast()
// Deletes the last occurence of int n and returns a pointer to the deleted Node.
Node deletelast(List L, int n);

// rotate()
// Rotates the list by the given int n.
void rotate(List L, int);

// reverse()
// Reverses the first n ints of the List
void reverse(List L, int n);

#endif
