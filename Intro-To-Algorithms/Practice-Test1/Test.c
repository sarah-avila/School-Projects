//-----------------------------------------------------------------------------
// Test1.c
// Practicing for CSE 101 Test - Linked Lists.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"List.h"

int main(int argc, char* argv[]) {

    List l = newList(); // declares Linked List
    int p = 4; // palindrome int

    // Checking size
    printf("size of list = %d\n", size(l));

    // Inserting
    insert(l, "1", 10);
    insert(l, "2", 20);
    insert(l, "4", 30);
    insert(l, "3", 40);
    insert(l, "5", 40);
    insert(l, "6", 30);
    insert(l, "7", 20);
    insert(l, "8", 10);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // Checking size
    printf("size of list = %d\n", size(l));

    // palindrome()
    p = palindrome(l);
    printf("palindrome = %d\n", p);

    // Dedup()
    printf("dedup time\n");
    dedup(l);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // palindrome()
    p = palindrome(l);
    printf("palindrome = %d\n", p);

    // Inserting
    insert(l, "9", 40);
    insert(l, "10", 30);
    insert(l, "11", 20);
    insert(l, "12", 10);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // deletelast()
    deletelast(l, 10);
    deletelast(l, 40);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // rotate()
    rotate(l, 2);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // Dedup()
    printf("dedup time\n");
    dedup(l);

    // Print List
    printf("printing list!\n");
    ListToString(l);

    // reverse()
    //reverse(l, 10);

    // Print List
    //printf("printing list!\n");
    //ListToString(l);

    // Free List
    freeList(&l);

    return(EXIT_SUCCESS);

}
