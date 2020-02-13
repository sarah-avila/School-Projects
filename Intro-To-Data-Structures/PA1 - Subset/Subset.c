//-----------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// October 10, 2019
//
// Subset.c
// A program that prints out all k-element subsets of the n-element set
// {1, 2, 3, ... , n},  where both n and k are given on the command line.
// Compile: gcc -std=c99 -Wall -o Subset Subset.c
// Run: Subset
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100
#define arrayLength MAX_SIZE+1

int isInt(char c[]);
void printSet(int B[], int n);
void printSubsets(int B[], int n, int k, int i);

int main(int argc, char *argv[]) {
        int i;
        int j = 1;
        int n = atoi(argv[1]);
        int k = atoi(argv[2]);
        int num1;
        int num2;
//      int arrayEx[5] = {1, 1, 1, 1, 1};
        int bitArray[arrayLength];
        if(n == 0) {
                printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
        }
        for (i = 1; argv[i] != 0; i++){
                if(isInt(argv[i]) == 0 || argc > 3) {
                        printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
                        break;
                }
                else {
                        num1 = n;
                        num2 = k;
                        if(num1 > num2) {
                                   break;
                        }
                        else
                                 printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
                   }
        }
        //printSet(arrayEx, 5);
        printSubsets(bitArray, n, k, j);
        return EXIT_SUCCESS;
}

int isInt(char c[]){
        int i;
        for(i = 0; c[i] != 0; i++){
           if(!isdigit(c[i])){
                return 0;
           }
        }
        return 1;
}

void printSet(int B[], int n) {
        int i;
        int count = 0;
        printf("{");
        for(i = 1; i < n+1; i++){
                if(B[i] == 1){
                        if(count>0) {
                                printf(", %i", i);
                        }
                        else{
                                printf("%i", i);
                                count++;
                        }
                }
        }
        printf("}\n");
}

void printSubsets(int B[], int n, int k, int i){
        if(k == 0){
                printSet(B, n);
                return;
         }
        if(k > (n - i + 1)){
                return;
        }
        B[i] = 1;
        printSubsets(B, n, k-1, i+1);
        B[i] = 0;
        printSubsets(B, n, k, i+1);
        }
