// ----------------------------------------------------------------------------
// nqueens.c
// Finds a solution (if applicable) for the n-Queens problem using
// a 2D array and a stack.
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tempMax 22

// function prototypes
int findSolutions(int** B, int n, int row);
void printBoard(int** B, int n);
void printSolutions(int** B, int n, int answer);
void placeQueen(int** B, int n, int i, int j);
void removeQueen(int** B, int n, int i, int j);

// main function
int main(int argc, char* argv[]) {
    FILE *in, *out;       // declare input and output files
    int** board;          // declare 2D array for game board
    //int stack[];        // declare stack
    int column = 0;            // temp store int from parsing
    int row = 0;
    int n = 0;            // size of the board
    int i = 0; //j = 0; // loop variable
    char* line = NULL;
    int answer = 0;     // number of solutions (if applicable)

    // Check command line for the correct number of arguments
    if( argc!=3 ) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input files for reading
    if( (in=fopen(argv[1], "r"))==NULL ) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    if( (out=fopen(argv[2], "w"))==NULL ) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for line
    line = calloc(tempMax+1, sizeof(char));

    // Parse the ints from the input file
    while( fgets(line, tempMax, in)!=NULL ) {
      if(strcmp(line,"\n")!=0) {
        printf("first while loop\n");
        n = line[0] - '0';
        printf("n = %d\n", n);

        // Allocate memory for 2D array
        board = calloc((n+1)*(n+1), sizeof(int*));
        for(i = 0; i <= n+1; i++){
            board[i] = calloc(n+1, sizeof(int));
        }

        printf("line = %s\n", line);
        i = 1;
        i++;
        while(line[i]!='\n') {
          column = line[i]-'0';
          i = i+2;
          row = line[i]-'0';
          printf("column = %d, row = %d\n", column, row);
          placeQueen(board, n, column, row);

          printf("printing board ------------------------------------\n");
          printBoard(board, n);

          answer = findSolutions(board, n, 1);
          printf("arrived back to main function\n");
          printSolutions(board, n, answer);
          i++;
          while(line[i]== ' ') {
            i++;
          }
      }
    }
  }



    // free memory for 2D array
    for(i = 0; i <= n+1; i++){
      free(board[i]);
    }
    free(board);
    return EXIT_SUCCESS;
}

//findSolutions function
int findSolutions(int** B, int n, int r){
    //int answer = 0; // initially false
    int c = 1;
    while(r <= n && c <= n) {
        if(B[r][c] == 1) {
            r++;
            continue;
        }
        if(B[r][c] == 0){
            placeQueen(B, n, r, c);
            printf("printing board after place------------------------------------\n");
            printBoard(B, n);
            findSolutions(B, n, r+1);

            if(r==n) {
              //printSolutions(B, n);
              return 1;
              printf("returning to main function\n");
              printf("Viva le France\n");
            }
            removeQueen(B, n, r, c);
            printf("printing board after remove------------------------------------\n");
            printBoard(B, n);
        }
        c++;
   }
  // printf("answer = %d\n", answer);
   return 0;
}

//printBoard function
void printBoard(int** B, int n){
  printf("(");
    int i, j;
    for(i = 1; i < n+1; i++) {
      for(j = 1; j < n+1; j++){
        if(i == n && j == n){
            printf("%d)\n", B[i][j]);
            break;
        }
        else{
            printf("%d, ", B[i][j]);
        }
    }
      printf("\n");
    }
}

//printSolutions function
void printSolutions(int** B, int n, int a) {
  printf("entering printSolutions\n");
  int i, j = 0;
  printf("ANSWER: \n");
  //check if last row has a queen
  for(i = 1; i <= n; i++ ) {
      if(B[n][i] == 1) {
        a = 1;
      }
  }
  if(a==0) {
       printf(" ");
       printf("ANSWER: No Solution\n");
       printf(" ");
   }
   else {
     printf("answer = 1! printing board\n");
       printBoard(B, n);
            for(i = 1; i <= n; i++) {
              for(j = 1; j <=n; j++) {
                if(B[i][j] == 1) {
                  printf("%d %d\n", j, i);
                }
              }
            }
  }
  printf("answer = %d\n", a);
  return;
}

//placeQueen function
void placeQueen(int** B, int n, int i, int j){
printf("entering placeQueen\n");
B[i][j] = 1;
B[i][0] = j;
int k;
int l = j;
for(k = i; k < n; k++){          // CHANGED n+1 to n
   B[k+1][l] += -1;              // decrementing vertical by -1
}
l = j;
for(k = i; k > 1; k--) {      // decrementing upward vertical by -1
       B[k-1][l] += -1;
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
  printf("j = %d, n+1 = %d_________________________________________________\n", j, n+1);
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
      for(k = i; k < n; k++){      // decrememting downward diagonal right by -1
         if(l < n) {
         B[k+1][l+1] += -1;
         l++;
         }
      }
      l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
          if(l < n) {
            B[k-1][l+1] += -1;
            l++;
          }
      }
      k = i;
      for(l = j; l > 1; l--){     // decrementing downward diagonal left by -1
         if(k<n){
         B[k+1][l-1] += -1;
         k++;
         }
      }
       k = i;
       for(l = j; l > 1; l--) {       // decrementing upward diagonal left by -1
          if(k > 1) {
            B[k-1][l-1] += -1;
            k--;
          }
      }
}
}

//removeQueen function
void removeQueen(int** B, int n, int i, int j){
//   printf("entering removeQueen\n");
//   for(i=1; i < n+1; i++) {
//     for(j=1; j < n+1; j++) {
//       B[i][j] = 0;
//     }
//   }

  B[i][j] = 0;
B[i][0] = 0;
int k;
int l = j;
for(k = i; k < n; k++){          // CHANGED n+1 to n
   B[k+1][l] += 1;              // // incrementing vertical by 1
}
l = j;
for(k = i; k > 1; k--) {      // incrementing upward vertical by 1
       B[k-1][l] += 1;
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
         if( l < n) {            // incrementing downward diagonal right by 1
         B[k+1][l+1] += 1;
         l++;
         }
      }
      l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
          if(l < n) {
            B[k-1][l+1] += 1;
            l++;
          }
      }
      k = i;
      for(l = j; l > 1; l--){     // incrementing downward diagonal left by 1
         if(k < n){
         B[k+1][l-1] += 1;
         k++;
         }
      }
       k = i;
       for(l = j; l > 1; l--) {       // incrementing upward diagonal right by 1
          if(k > 1) {
            B[k-1][l-1] += 1;
            k--;
          }
      }
  }
}
