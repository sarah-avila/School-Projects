//-----------------------------------------------------------------------------
// bard.c
// A client for the List ADT that completes a word analysis of
// Shakespeare's literary works.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"
#define arrayLength 40

int main(int argc, char* argv[]) {
    FILE *wsText, *in, *out;             // input files wsText and in and output file out                        //
    List lengths[arrayLength];          // declares array of Linked Lists
    char* line = NULL;                  // the input string
    char* answerKey = "answer!\n";      // the answer string that is printed to the output file
    int strLength = 0;                  // length of the input string
    int findValue = 0;                  // the value returned when searching for a given key
    int givenL = 0, givenF = 0;         // the given ints from the input file
    int i = 0;                          // loop variables

    // Check command line for the correct number of arguments
    if( argc!=3 ) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input files for reading
    if( (wsText=fopen("shakespeare-cleaned5.txt", "r"))==NULL || (in=fopen(argv[1], "r"))==NULL ) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    if( (out=fopen(argv[2], "w"))==NULL ) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each List
    for(i = 0; i < arrayLength; i++) {
        lengths[i] = newList();
    }

    // Allocate memory for line
    line = calloc(arrayLength+1, sizeof(char));

    // Read each line of the input file and either insert a new Node or update the Node's value
    while(fscanf(wsText, "%s\n", line) != EOF) {
        strLength = strlen(line);
        findValue = find(lengths[strLength], line);
        if(findValue==-1){                          // if line is not found
            // printf("\n");
            insert(lengths[strLength], line, 1);
        }
        else {
            // printf("\n");
            updateValue(lengths[strLength], line);
        }
    }

     // printf("PRINTING ALL LISTS -----------------------------------------\n");
     // for(i=1; i < arrayLength; i++) {
     //     printf("Printing List %d --------------------------------------\n", i);
     //     ListToString(lengths[i]);
     // }

    // Sorting the List in lexiocographic order using Insertion Sort
    for(i = 1; i < arrayLength; i++) {
        if(size(lengths[i])!=0) {
            insertionSort(lengths[i]);
            //insertionSortA(lengths[i]);
        }
    }

    // printf("PRINTING ALL LISTS -----------------------------------------\n");
    // for(i=1; i < arrayLength; i++) {
    //     printf("Printing List %d --------------------------------------\n", i);
    //     ListToString(lengths[i]);
    // }

    // Read each line of two integers from the input file
    while( !feof(in) ) {
        fscanf(in, "%d %d\n", &givenL, &givenF);
            answerKey = traverse(lengths[givenL], givenF);
            if(answerKey==NULL) {
                fprintf(out, "-\n");
            }
            else {
                fprintf(out, "%s\n", answerKey);
            }
    }

    // READ FROM input
    //Do STUFF
    //PRINT TO OUTPUT

    // Free heap memory
    for(i = 0; i < arrayLength; i++) {    // frees all Lists
        freeList(lengths);
    }
    free(line);

    // Close input and output files
    fclose(in);
    fclose(out);

    return(EXIT_SUCCESS);
}
