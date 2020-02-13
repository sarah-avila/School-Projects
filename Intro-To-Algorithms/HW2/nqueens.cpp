// ----------------------------------------------------------------------------
// nqueens.cpp
// Finds a solution (if applicable) for the n-Queens problem using
// a 2D array and a stack.
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <stdio.h>
#define tempMax 22

using namespace std;

// function prototypes
int findSolutions(int **B, int n);
void printBoard(int **B, int n);
void printSolutions(int **B, int n, int answer, FILE* output);
void placeQueen(int **B, int n, int i, int j);
void removeQueen(int **B, int n, int i, int j);

//Queen class
struct Queen
{
	int column;
	int row;
};

// findSolutions function
int findSolutions(int **B, int n) {
  stack<class Queen> stack;        // declare stack
  int c, r;                        // column and row variables
  int queenPlaced = 0;
  int ifSolved;
  Queen start, stacktop, toPush;

  // find first available row
  for(int i = 1; i <= n; i++) {
    if(B[i][0]==0) {
      r = i;
      break;
    }
  }

  // push Queen to 0th column
  start.column = 0;
  start.row = r;
  stack.push(start);

  while( !stack.empty() ) {
    // get the next Queen on the stack
    stacktop = stack.top();
    stack.pop();
    // remove Queen if not in 0 column
    if( stacktop.column != 0 ) {
      removeQueen(B, n, stacktop.row, stacktop.column);
    }
    r = stacktop.row;

    queenPlaced = 0;
    for(c = stacktop.column+1; c <= n; c++) {
      // if there are no available spaces
      if( c >= n && B[r][c] == -1 ) {
        // go to the previous Queen on the stack
        break;
      }
      // if available space is found
      if(B[r][c] == 0) {
        // place the Queen on the board
        placeQueen(B, n, r, c);
        toPush.column = c;
        toPush.row = r;
        stack.push(toPush);
        queenPlaced = 1;
        break;
      }
    }
	// if there are no available spaces
    if( c >= n && B[r][c] == -1 ) {
      continue;
    }
    ifSolved = 1;
    for(int i = 1; i <=n; i++) {
	  // if there is not a solution in one of the rows
      if(B[i][0] == 0) {
         ifSolved = 0;
      }
    }

    if(ifSolved==1) {
      return 1;
    }

    if(queenPlaced == 1) {
     // find next available row
        for(int i = stacktop.row+1; i <= n; i++) {
          if(B[i][0]==0) {
            toPush.column = 0;
            toPush.row = i;
            stack.push(toPush);
            break;
          }
        }
     }
  }
  return 0;
}

//printBoard function
void printBoard(int** B, int n)
{
  //printf("(");
    int i, j;
    for(i = 0; i < n+1; i++) {
      for(j = 0; j < n+1; j++){
        if(i == n && j == n){
            //printf("%d)\n", B[i][j]);
            break;
        }
        else{
            //printf("%d, ", B[i][j]);
        }
      }
     // printf("\n");
    }
}

//printSolutions function
void printSolutions(int **B, int n, int a, FILE* output)
{
  int i, j = 0;

  //check if last row has a queen
  for(i = 1; i <= n; i++ ) {
		if(B[n][i] == 1) {
			a = 1;
    }
  }
  if(a==0) {
    //printf("\n");
    //print to out file
    fprintf(output, "No Solution\n");
    //printf("\n");
	}
	else {
    //printBoard(B, n);
    for(i = 1; i <= n; i++) {
	  for(j = 1; j <=n; j++) {
		// if a space on the board has a Queen
	    if(B[i][j] == 1) {
          if(i==n) {
            fprintf(output, "%d %d\n", i, j);
          }
          else {
          // print in out file
          fprintf(output, "%d %d ", i, j);
		  //printf("%d %d ", j, i);
          }
        }
      }
		 }
	 }
  return;
}

//placeQueen function
int checkQueen(int **B, int n, int i, int j)
{
	B[i][j] = 1;
	B[i][0] = j;
	int k;
	int l = j;
	for(k = i; k < n; k++){          // CHANGED n+1 to n
		if(B[k+1][l] == 1){
      return 0;
    }               // decrementing vertical by -1
	}
	l = j;
	for(k = i; k > 1; k--) {      // decrementing upward vertical by -1
		if(B[k-1][l] == 1) {
      return 0;
    }
  }
	if(j == 1){
		l = j;
		for(k = i; k < n; k++){
			if(l < n){
				if(B[k+1][l+1] == 1) {
          return 0;
        }             // decrememting diagonal right by -1
				l++;
			}
	  }
    l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
				if(l < n) {
					if(B[k-1][l+1] == 1) {
            return 0;
          }
          l++;
        }
      }
	}
	else if(j == n+1){
		k = i;
		for(l = j; l > 1; l--){     // decrementing diagonal left by -1
			if(k < n+1){
				if(B[k+1][l-1] == 1) {
          return 0;
        }
				k++;
      }
    }
    k = i;
				for(l = j; l > 1; l--) {       // decrementing upward diagonal left by -1
					if(k > 1) {
						if(B[k-1][l-1] == 1) {
              return 0;
            }
            k--;
          }
				}
  }
	else {                               // decrementing both diagonals by -1
		l = j;
			for(k = i; k < n; k++){      // decrememting downward diagonal right by -1
				if(l < n) {
					if(B[k+1][l+1] == 1) {
            return 0;
          }
          l++;
        }
      }
      l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
				if(l < n) {
					if(B[k-1][l+1] == 1) {
            return 0;
          }
          l++;
        }
      }
      k = i;
      for(l = j; l > 1; l--){     // decrementing downward diagonal left by -1
				if(k<n){
					if(B[k+1][l-1] == 1) {
            return 0;
          }
					k++;
        }
      }
      k = i;
				for(l = j; l > 1; l--) {       // decrementing upward diagonal left by -1
					if(k > 1) {
						if(B[k-1][l-1] == 1) {
              return 0;
            }
            k--;
          }
				}
		}
  return 1;
}

//placeQueen function
void placeQueen(int **B, int n, int i, int j)
{
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
    l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
				if(l < n) {
					B[k-1][l+1] += -1;
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
    k = i;
				for(l = j; l > 1; l--) {       // decrementing upward diagonal left by -1
					if(k > 1) {
						B[k-1][l-1] += -1;
            k--;
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
void removeQueen(int** B, int n, int i, int j)
{
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
    l = j;
      for(k = i; k > 1; k--) {       // decrementing upward diagonal right by -1
				if(l < n) {
					B[k-1][l+1] += 1;
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
    k = i;
				for(l = j; l > 1; l--) {       // decrementing upward diagonal left by -1
					if(k > 1) {
						B[k-1][l-1] += 1;
            k--;
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


// main function
int main(int argc, char* argv[])
{
  int** board;                    // declare 2D array for game board
  char line[50];                   // store the input string from the file
  int column = 0;                // temp store int from parsing
  int row = 0;
  int n = 0;                     // size of the board
  int i = 0, j = 0;               // loop variable
  int hasCollisions = 0;
  int answer = 0;             // number of solutions (if applicable)

	// Check command line for the correct number of arguments
	if (argc != 3)
	{
		throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
	}

	FILE* input;       // input file
  FILE* output;      // output file

	// Open input files for reading
    if( (input=fopen(argv[1], "r"))==NULL ) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    if( (output=fopen(argv[2], "w"))==NULL ) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

  // Parse the ints from the input file
  while( fgets(line, tempMax, input)!=NULL ) {
		if(strcmp(line,"\n")!=0) {

      i=1;
      n = line[0] - '0';
      if(n == 1){
		// check if it is a double digit number
        if(line[1] - '0' < 11 && line[1] - '0' >= 0) {
          n = (line[1] - '0') + 10;
          i++;
        }
      }

			// Allocate memory for 2D array
      board = new int*[n+1];
			for(j = 0; j <= n; j++)  {
				board[j] = new int[n+1];
			}

//       for(i = 0; i <= n; i++)  {
//         for(j = 0; j <= n; j++) {
// 				  board[i][j] = 0;
//         }
// 			}
//       printf("Printing board\n");
//       printBoard(board, n);

     // cout << "line = " << endl;
	    //cout << line << endl;

      i++;
      while(line[i]!='\n') {
				row = line[i]-'0';
        if(row == 1){
          if(line[i + 1] - '0' < 11 && line[i + 1] - '0' >= 0) {
            row = (line[i + 1] - '0') + 10;
            i++;
          }
        }
        i = i+2;
        column = line[i]-'0';
        if(column == 1){
          if(line[i + 1] - '0' < 11 && line[i + 1] - '0' >= 0) {
            column = (line[i + 1] - '0') + 10;
            i++;
          }
        }
        placeQueen(board, n, column, row);
        hasCollisions = checkQueen(board, n, column, row);

        if(hasCollisions == 0) {
          break;
        }
        printBoard(board, n);

        i++;
        while(line[i]== ' ') {
					i++;
        }
      }

      if(hasCollisions==0) {
        printSolutions(board, n, 0, output);
      }
      else{
        answer = findSolutions(board, n);
        printSolutions(board, n, answer, output);
      }
    }
  }

	// Deallocate memory for 2D array
	for(i = 0; i <= n; i++) {
		delete board[i];
	}
	delete[] board;
  return EXIT_SUCCESS;
}
