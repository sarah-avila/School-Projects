//---------------------
// QueensTest.c
//---------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printArrayNew(int** B,int n);
void placeQueen(int** B, int n, int i, int j);
void removeQueen(int** B, int n, int i, int j);
int findSolutions(int** B, int n, int i, char* mode);
void printBoard(int** B, int n);

// Test placeQueens
int main(int argc, char* argv[]){
int  A4[5][5]= {{0,0,0,0,0},{2,0,1,0,0},{4,-1,-1,-1,1},{1,1,-1,-1,-2},{0,-1,-3,0,-1}};
int *B4[5] ;
for(int i=0;i<5;i++){
  B4[i] = (int *)A4[i];
}

printf("yo\n");
//placeQueen(B2,4,3,1);
//printf("done with placeQueen\n");
//printArrayNew(B2,4);

//removeQueen( B3, 4, 4 , 3);
//printf("%d:%d\n",B3[4][3],B3[4][0]);
printf("%d\n",findSolutions( B4, 4, 4 , ""));
return EXIT_SUCCESS;
}

//PLACE QUEEN
void placeQueen(int** B, int n, int i, int j){
B[i][j] = 1;
B[i][0] = j;
int k;
int l = j;
printf("nice\n");
for(k = i; k < n; k++){ //CHANGED n+1 to n !!!!!!!!!!!!!!!!!!!!!!!!!!!!
  printf("1\n");        // decrementing vertical by -1
   B[k+1][l] += -1;
}
if(j == 1){
  printf("2\n");
   l = j;
   for(k = i; k < n; k++){ //CHANGED n+1 to n !!!!!!!!!!!!!!!!!!!!!!!!!!
      printf("3\n");// decrememting diagonal right by -1
      if(l < n){      // CHANGED n+1 to n !!!!!!!!!!!!!!!!!!!!!!!!!!!!
      B[k+1][l+1] += -1;
      l++;
      }
   }
}
else if(j == n+1){
  printf("bruh\n");
   k = i;
   for(l = j; l > 1; l--){     // decrementing diagonal left by -1
      if(k < n+1){
      B[k+1][l-1] += -1;
      k++;
      }
   }
}
else {
     printf("omg\n");
      l = j;
      for(k = i; k < n; k++){      // decrememting diagonal right by -1
         if(l < n) {
         B[k+1][l+1] += -1;
         l++;
         }
      }
      k = i;
      for(l = j; l > 1; l--){     // decrementing diagonal left by -1
         if(k< n){
         B[k+1][l-1] += -1;
         k++;
         }
      }
}
}

// REMOVE QUEEN
void removeQueen(int** B, int n, int i, int j){
B[i][j] = 0;
B[i][0] = 0;
int k;
int l = j;
for(k = i; k < n; k++){          // incrementing vertical by 1
   B[k+1][l] += 1;               // CHANGED from n+1 to n
}
printf("dala\n");
if(j == 1){
  printf("dala\n");
   l = j;
   for(k = i; k < n; k++){      // incrementing diagonal right by 1
      if(l < n) {
      B[k+1][l+1] += 1;
      l++;
      }
   }
}
else if(j == n+1){
  printf("yeah\n");
   k = i;
   for(l = j; l > 1; l--){     // incrementing diagonal left by 1
      if(k < n+1) {
      B[k+1][l-1] += 1;
      k++;
      }
   }
}
else {
  printf("ohOH\n");                         // incrementing both diagonals by 1
      l = j;
      for(k = i; k < n; k++){
         printf("f\n");
         if( l < n) {          // incrementing diagonal right by 1
         B[k+1][l+1] += 1;
         l++;
         }
      }
      printf("ff\n");
      k = i;
      for(l = j; l > 1; l--){     // incrementing diagonal left by 1
         if(k < n){
         B[k+1][l-1] += 1;
         k++;
         }
      }
}
}

//FIND SOLUTIONS
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
        printf("hehe\n");
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

void printArrayNew(int** B,int n) {
       // char* result;
        printf("{");
        for(int i=0;i<=n;i++) {
            printf("{");
            for(int j=0;j<=n;j++) {
                if(j!=n)
                    printf("%d,",B[i][j]);
                else {
                    printf("%d",B[i][j]);
                }
            }
            printf("}");
            if(i!=n)
                printf(",");
        }
        printf("}\n");
        //return result;
}
