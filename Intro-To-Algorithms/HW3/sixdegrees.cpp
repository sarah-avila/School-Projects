//-----------------------------------------------------------------------------
// sixdegrees.c
// A client for the List ADT that parses a dataset into an adjacency list
// implementation of a graph and performs shortest path computations.
//-----------------------------------------------------------------------------
//#include<stdlib.h>
//#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<list>
#include<queue>
#include<unordered_map>
#include<stack>
#include<algorithm>
#define numOfVertices 155270
#define lineLength 100

using namespace std;

struct Actor;
struct Paths;

// declare paths struct
struct Paths {
    string movieName;
    Actor* pred;
    Actor* next;
    Paths(string movieName, Actor* next, Actor* pred) : movieName(movieName), next(next), pred(pred) {}
};

// declare actor struct
struct Actor {
    string name;
    //bool visited;
    vector<Paths*> paths;
    Actor(string name) : name(name) {}
};

int returnToSource(unordered_map<string, Paths*> findPath, Actor* current, string source, FILE* out) {
    stack<Actor*> stack;
    // while the current name is not the source
    while(current->name!=source) {
        stack.push(current);
        current = findPath[current->name]->pred;
    }

    // Print output
    while(!stack.empty()) {
        current = stack.top();
        stack.pop();

        fprintf(out, "%s -(%s)- ", findPath[current->name]->pred->name.c_str(), findPath[current->name]->movieName.c_str());

    }
    fprintf(out, "%s\n", current->name.c_str());


    return 0;
}

// runBFS() function
int runBFS(unordered_map<string, Actor*> graph, string source, string dest, FILE* out) {
    queue<Actor*> queue;      // queue for BFS
    Actor* top;
    unordered_map<string, Paths*> findPath;  // mapping path of searching for dest
    string toInsertActor;
    Paths* toInsertPath;
    vector<Paths*> currPathsList;

    // push source onto queue
    queue.push(graph[source]);

    while(!queue.empty()) {
        top = queue.front();
        queue.pop();
        // if destination is found
        if(top->name==dest) {
            returnToSource(findPath, top, source, out);
        }

        currPathsList = top->paths;
        for(int i = 0; (unsigned)i < currPathsList.size(); i++) {
            if(findPath.count(top->paths[i]->next->name)==0) {
                toInsertActor = top->paths[i]->next->name;
                toInsertPath = top->paths[i];
                toInsertPath->pred = top;
                currPathsList.at(i)->pred = top;
                findPath[toInsertActor] = currPathsList.at(i);
                queue.push(currPathsList.at(i)->next);
            }
        }
    }
    findPath.clear();
    return 0;
}

int main(int argc, char* argv[]) {
    FILE *in;
    FILE *out;                  // input and output files
    FILE *imdb;                 // file of imbd info about movies and actors
    unordered_map<string, Actor* > graph;  //unordered map for graph
    char* line = NULL;                  // input string
    char* token;                 // tokens of the input string
    char* actor1;                       // first actor of input query
    char* actor2;                       // second actor of input query
    int i = 0;                          // loop variable

    // Check command line for the correct number of arguments
    if( argc!=3 ) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input files for reading
    if( (in=fopen(argv[1], "r"))==NULL || (imdb=fopen("cleaned_movielist.txt", "r"))==NULL ) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    if( (out=fopen(argv[2], "w"))==NULL ) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for char arrays
    line = (char*)calloc(lineLength+1, sizeof(char));

    // Read each line of the imbd file and insert into the vectors
    while( fgets(line, lineLength, imdb)!=NULL ) {
        if( strcmp(line,"\n")!=0 ) {
            // declare lineVector
            vector<string> lineVector;
            token = strtok(line, " \n");

            token = strtok(NULL, " \n");
            while( token!=NULL ) {
                lineVector.push_back(string(token));
                token = strtok(NULL, " \n");
            }

            // Insert (key, value) pairs into graph
            for(i = 1; (unsigned)i < lineVector.size(); i++) {
        

                    // actor has not been inserted into graph yet
                    if(graph.find(lineVector[i])==graph.end()) {
                        Actor* a = new Actor(lineVector.at(i));
                        graph[lineVector.at(i)] = a;
                    }
            }
          for(int i = 1; (unsigned)i < lineVector.size(); i++) {
            for(int j = 1; (unsigned)j < lineVector.size(); j++) {
              if(i!=j) {
                 Paths* p = new Paths(lineVector.at(0), graph[lineVector.at(j)], graph[lineVector.at(i)]);
                 graph[lineVector.at(i)]->paths.push_back(p);
              }
            }
         }
        }

    }

    actor1 = (char*)calloc(lineLength+1, sizeof(char));
    actor2 = (char*)calloc(lineLength+1, sizeof(char));
    strcpy(line, "");

    // Read each line of the input file and find shortest paths
    while( fscanf(in, "%s %s\n", actor1, actor2)!=EOF ) {
        string actor1Str(actor1);
        string actor2Str(actor2);

        // check if iterator points to end of list
        if(graph.find(actor1Str)==graph.end() || graph.find(actor2Str)==graph.end()) {
            // actors are not in actors vector
            fprintf(out, "Not present\n");
        }
        // if actor1 and actor2 are equal
        else if( actor1Str.compare(actor2Str)==0 ) {
            fprintf(out, "%s\n", actor1);
        }
        else {
            runBFS(graph, actor1Str, actor2Str, out);
        }
    }

    delete(line);

    return (EXIT_SUCCESS);
}
