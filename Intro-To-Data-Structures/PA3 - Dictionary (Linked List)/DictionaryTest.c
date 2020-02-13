//-----------------------------------------------------------------------------
// DictionaryTest.c
// A test client for the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

int main(){
  Dictionary A = newDictionary();
  char* str;
  char* k;
  char* v;
  char* word1[] = {"one","two","three","four","five","six","seven"};
  char* word2[] = {"cat","dog","cow","horse","mouse","sheep","bird"};
  int i;
   for(i=0; i<7; i++){
      insert(A, word1[i], word2[i]);
   }

   // print out the Dictionary
   printf("\n");
   printf("--------------------------------------\n");
   printf("Printing Dictionary:\n");
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   printf("--------------------------------------\n");

   // print key and value strings
   printf("Printing keys and values:\n");
   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   printf("\n");
   printf("--------------------------------------\n");

    // insert(A, "five", "glow"); // duplicate key error
    delete(A, "one");
    delete(A, "three");
    delete(A, "seven");

   // print out the Dictionary
   printf("Printing Dictionary AFTER DELETE:\n");
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);
   printf("--------------------------------------\n");

   // print key and value strings
   printf("Printing keys and values AFTER DELETE:\n");
   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   printf("\n");
   printf("--------------------------------------\n");

   // delete(A, "one");  // key not found error

   // check size before and after makeEmpty()
   printf("Checking Size:\n");
   printf("size(A) = %d\n", size(A));
   printf("\n");
   printf("--------------------------------------\n");

   // make A empty, check size, print it out
   printf("Making Dictionary Empty:\n");
   makeEmpty(A);
   printf("size(A) = %d\n", size(A));
   printf("\n");
   printf("--------------------------------------\n");

   // free Dictionary
   freeDictionary(&A);

   return(EXIT_SUCCESS);
}
