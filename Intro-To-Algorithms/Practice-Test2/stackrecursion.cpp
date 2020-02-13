// -----------------------------------------------------------------------------
// stackrecursion.cpp
// Simulates recursion through a stack with the ouput using the List ADT
// -----------------------------------------------------------------------------

#include <iostream>
#include "list.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <math.h>
using namespace std;

// Pair class
// Stores a pair of strings to simulate recursion through a stack
class Pair
{
    public:
        string in_str;
        string fixed_str;
};

// allAnagrams()
// Prints all of the anagrams of a given string
List allAnagrams(string input) {
    List final_output; // generate empty list
    stack<class Pair> anagramStack; // empty stack that performs the recursion
    Pair init, stacktop; // create a pair to push, to start the stac
    init.in_str = input; // put the initial string
    init.fixed_str = ""; // this is the fixed string, initially empty
    anagramStack.push(init); // push this pair onto the top

    while(!anagramStack.empty()) // while the stack is non-empty
    {
        stacktop = anagramStack.top();// get the top pair in stack
        anagramStack.pop(); // remove the top element of stack
        if (stacktop.in_str.length() == 0) // input string is empty, so this is base case
        {
            final_output.insert(stacktop.fixed_str); // insert the fixed string onto list
            continue; // pop the next element of stack
        }
        string originalInput = stacktop.in_str;
        string originalAnagram = stacktop.fixed_str;
        for(int i = 0; (unsigned)i <= stacktop.in_str.length(); i++) {
            stacktop.in_str = originalInput;
            stacktop.fixed_str = originalAnagram;
            stacktop.fixed_str.push_back(stacktop.in_str.at(i));
            stacktop.in_str.erase(i, 1);
            anagramStack.push(stacktop);
        }
    }
    return final_output;
}

// language()
// Prints the set of all strings comprising of the characters in a given string
List language(string input, int k) {
    List final_output; // generate empty list
    stack<string> recurStack; // empty stack that performs the recursion
    recurStack.push(""); // push this string onto the top

    while(!recurStack.empty()){ // while the stack is non-empty
        string top = recurStack.top();
        recurStack.pop();
        if (top.length() == (unsigned)k)
        {
                final_output.insert(top); // insert the fixed string onto list
        }
        else {
               for(int i = 0; (unsigned)i < input.length(); i++) {
                   string toPush = top;
                   toPush = toPush + input[i];
                   recurStack.push(toPush);
                   if(toPush.length() < (unsigned)k){
                       final_output.insert(toPush);
                   }
               }
        }
    }
     return final_output;
}

// stretch()
// Given an integer k, prints all strings by repeating each character in order up to k times
List stretch(string input, int k) {
    List final_output;
    stack<class Pair> recurStack;
    Pair init, stacktop;
    init.in_str = input;
    init.fixed_str = "";
    recurStack.push(init);

    while(!recurStack.empty()) {
        stacktop = recurStack.top();
        recurStack.pop();
        if(stacktop.in_str.length()== 0) {
            final_output.insert(stacktop.fixed_str);
        }
        else {
            char c = stacktop.in_str.front(); // get front element
            stacktop.in_str.erase(0,1); // erase element
            for(int i = 0; i < k; i++) {
                stacktop.fixed_str = stacktop.fixed_str + c; // add element
                recurStack.push(stacktop);
            }
        }

    }
    return final_output;
}

int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in_str; // to store the input string from the file


    getline(input, in_str); // get the single string from the input file

    // initializing the linked list
    //List myList = allAnagrams(in_str);
    //List myList = language(in_str, 2);
    List myList = stretch(in_str, 2);

    myList.sort(); // sort the list

    output << myList.print("\n") << endl;  // print the list, using a new line as delimiter between items of the list

    myList.deleteList(); // free all the memory of this list

    input.close();
    output.close();
}
