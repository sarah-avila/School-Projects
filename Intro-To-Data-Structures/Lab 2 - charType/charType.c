//-----------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// October 17, 2019
//
// charType.c
// Takes two command line arguments giving the input and output file
// respectively, then classifies the characters on each line of the input file
// into 4 categories: alphabetic characters, numeric characters, punctuation,
// and white space. A report will be printed to the output file for each line
// giving the number of characters of each type and the characters themselves.
// Compile: $ gcc -std=c99 -Wall -o charType charType.c
// Run: charType
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// extract_chars function prototype
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// main function
int main(int argc, char* argv[]){
   int line_count = 1;
   int a_length;
   int n_length;
   int p_length;
   int w_length;
   FILE* in;   //input file
   FILE* out;  // output file
   char* line; // string holding input line
   char* alpha; // string holding alphabetic chars
   char* num;   // string holding numeric chars
   char* punct; // string holding punctuation
   char* space; // string holding white space

   // check command line for 3 arguments
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate char arrays on the heap
     line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
     alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
     num = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
     punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
     space = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
     assert( line!=NULL && alpha!=NULL && num!=NULL && punct!=NULL && space!=NULL );

     // read each line in input file, categorize characters
     while( fgets(line, MAX_STRING_LENGTH, in) !=NULL ){
        extract_chars(line, alpha, num, punct, space);

        fprintf(out, "line %d contains:\n", line_count);

        a_length = strlen(alpha);
        n_length = strlen(num);
        p_length = strlen(punct);
        w_length = strlen(space);

        if(a_length == 1){
           fprintf(out, "1 alphabetic character: %s\n", alpha);
        }
        if(a_length == 0 || a_length > 1){
           fprintf(out, "%d alphabetic characters: %s\n", a_length, alpha);
        }

        if(n_length == 1){
           fprintf(out, "1 numeric character: %s\n", num);
        }
        if(n_length == 0 || n_length > 1){
           fprintf(out, "%d numeric characters: %s\n", n_length, num);
        }

        if(p_length == 1){
           fprintf(out, "1 punctuation character: %s\n", punct);
        }
        if(p_length == 0 || p_length > 1){
           fprintf(out, "%d punctuation characters: %s\n", p_length, punct);
        }

        if(w_length == 1){
           fprintf(out, "1 whitespace character: %s\n", space);
        }
        if(w_length == 0 || w_length > 1){
           fprintf(out, "%d whitespace characters: %s\n", w_length, space);
        }
        line_count++;
  }

     // free heap memory
     free(line);
     free(alpha);
     free(num);
     free(punct);
     free(space);

     // close input and output files
     fclose(in);
     fclose(out);

     return  EXIT_SUCCESS;
  }

  //extract_chars definition
void extract_chars(char* s, char* a, char* d, char* p, char* w){
   int i = 0, j = 0, k = 0, l = 0, m  = 0;
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isalpha( (int) s[i] )) {
         a[j++] = s[i];
      }
      if( isdigit( (int) s[i] )) {
         d[k++] = s[i];
      }
      if( ispunct( (int) s[i] )) {
         p[l++] = s[i];
      }
      if( isspace( (int) s[i] )) {
         w[m++] = s[i];
      }
      i++;
   }
   a[j] = '\0';
   d[k] = '\0';
   p[l] = '\0';
   w[m] = '\0';
}
                            
