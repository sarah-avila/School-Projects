//--------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// October 24, 2019
//
// Queens.c
// Given an integer n, this program will solve the n-Queens puzzle problem.
// In a n x n chess board, n queens will be placed on the board so that no
// queen will cross another horizontally, vertically, or diagonally. There are
// two modes: normal and verbose. Normal mode prints the number of solutions to
// n_Queens, while verbose mode prints all solutions to n-Queens followed by the
// number of solutions.
// Compile: $gcc -std=c99 -Wall -o Queens Queens.c
// Run: Queens
// -------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//fuction prototypes
char* mode;
int ifCorrectInput(int argc,  char* argv[]);
void placeQueen(int** B, int n, int i, int j);
void removeQueen(int** B, int n, int i, int j);
void printBoard(int** B, int n);
int findSolutions(int** B, int n, int i, char* mode);

//main function
int main(int argc, char* argv[]) {
int i, n, s;

if(argc > 1  && argc < 4) {
   if(ifCorrectInput(argc, argv)){               // if argv[] has the correct format
      int** B;
     // i = 0;
      if(!strcmp(mode, "verbose")){
         n = atoi(argv[2]);
      }
      else
         n = atoi(argv[1]);
      B = calloc((n+1)*(n+1), sizeof(int*));    // create 2D array
      for(i = 0; i <= n+1; i++){
         B[i] = calloc(n+1, sizeof(int));
      }
      i = 1;
      if(!strcmp(mode, "verbose")){
         s = findSolutions(B, n, i, mode);
      }
      else{
        s = findSolutions(B, n, i, mode);
      }

      for(i = 0; i <= n+1; i++){
        free(B[i]);
      }
      free(B);
  }
  else{
      //CHANGED error message
      printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
      return EXIT_FAILURE;
  }
}
else{
    //CHANGED error message
    printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
    return EXIT_FAILURE;
}
if(s == 1){                                     // print the number of solutions
   printf("%d-Queens has 1 solution\n", n);
}
else{
   printf("%d-Queens has %d solutions\n", n, s);
}
return EXIT_SUCCESS;
}

//ifCorrectInput function
int ifCorrectInput(int argc, char* argv[]){
if(argc==2){
   if(isdigit(*argv[1])){
      int i = atoi(argv[1]);
      if(i > 0 && i < 16){
         mode = "normal";                    // if in normal mode
         return 1;
      }
   }
}
if(argc == 3){
     if(!strcmp(argv[1], "-v")){
         if(isdigit(*argv[2])){
         int j = atoi(argv[2]);
            if(j > 0 && j < 16){
               mode = "verbose";               // if in verbose mode
               return 1;
            }
         }
      else
         return 0;
   }
   else
      return 0;
}
return 0;
}

//findSolutions function
int findSolutions(int** B, int n, int i, char* mode){
int sum = 0;
if(i > n){
   if(!strcmp(mode, "verbose")){
      printBoard(B, n);
   }
   return 1;
}
else{
   int j;
   for(j = 1; j < n+1; j++){
      if(B[i][j] == 0){
         placeQueen(B, n, i, j);
         sum += findSolutions(B, n, i+1, mode);
         removeQueen(B, n, i, j);
         }
   }
}
return sum;
}

//printBoard function
void printBoard(int** B, int n){
printf("(");
int i;
for(i = 1; i < n+1; i++) {
   if(i == n){
      printf("%d)\n", B[i][0]);
      break;
   }
   else{
      printf("%d, ", B[i][0]);
   }
}
}

//placeQueen function
void placeQueen(int** B, int n, int i, int j){
B[i][j] = 1;
B[i][0] = j;
int k;
int l = j;
for(k = i; k < n; k++){          // CHANGED n+1 to n
   B[k+1][l] += -1;              // decrementing vertical by -1
}
if(j == 1){
   l = j;
   for(k = i; k < n; k++){
      if(l < n){
      B[k+1][l+1] += -1;        // decrememting diagonal right by -1
      l++;
      }
   }
}
else if(j == n+1){
   k = i;
   for(l = j; l > 1; l--){     // decrementing diagonal left by -1
      if(k < n+1){
      B[k+1][l-1] += -1;
      k++;
      }
   }
}
else {                               // decrementing both diagonals by -1
      l = j;
      for(k = i; k < n; k++){      // decrememting diagonal right by -1
         if(l < n) {
         B[k+1][l+1] += -1;
         l++;
         }
      }
      k = i;
      for(l = j; l > 1; l--){     // decrementing diagonal left by -1
         if(k<n){
         B[k+1][l-1] += -1;
         k++;
         }
      }
}
}

//removeQueen function
void removeQueen(int** B, int n, int i, int j){
B[i][j] = 0;
B[i][0] = 0;
int k;
int l = j;
for(k = i; k < n; k++){          // CHANGED n+1 to n
   B[k+1][l] += 1;              // // incrementing vertical by 1
}
if(j == 1){
   l = j;
   for(k = i; k < n; k++){      // incrementing diagonal right by 1
      if(l < n) {
      B[k+1][l+1] += 1;
      l++;
      }
   }
}
else if(j == n+1){
   k = i;
   for(l = j; l > 1; l--){     // incrementing diagonal left by 1
      if(k < n+1) {
      B[k+1][l-1] += 1;
      k++;
      }
   }
}
else {                           // incrementing both diagonals by 1
      l = j;
      for(k = i; k < n; k++){
         if( l < n) {            // incrementing diagonal right by 1
         B[k+1][l+1] += 1;
         l++;
         }
      }
      k = i;
      for(l = j; l > 1; l--){     // incrementing diagonal left by 1
         if(k < n){
         B[k+1][l-1] += 1;
         k++;
         }
      }
}
}
