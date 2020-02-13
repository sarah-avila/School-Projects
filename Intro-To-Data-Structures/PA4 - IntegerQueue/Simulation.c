//------------------------------------------------------------------------------
// Sarah Avila
// cruzid: satavila
// CSE 15: Intro to Data Structures
// December 1, 2019
//
// Simulation.c
// Given a number of m jobs, each with specific arrival times and durations,
// the simulation prints the state of queues with n processors to the trace
// output file. The total wait time, the maximum wait time, and thh average wait
// time over all m jobs are printed in the report output file.
// Compile: $ gcc -std=c99 -Wall -o Simulation Simulation.c
// Run: Simulation in
//------------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
//#include<math.h>
#include"Job.h"
#include"IntegerQueue.h"

// getJob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE* in){
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}

// main()
int main(int argc, char* argv[]){
  FILE *in, *trc, *rpt;   // input file in and two output files trace and report
  Job* backup;            // array to store Jobs in order
  IntegerQueue* queue;    // array to store processor and storage IntegerQueues
  char* trcName;          // string for the name of the trace file
  char* rptName;           // string for the name of the report file
  int queueElement = 0;   // used to enqueue / dequeue elements
  int time = 0;           // the current time in the simulation
  int totalWait = 0;      // the total wait for a certain Job
  int maxWait = 0;        // the maximum wait for a certain Job
  double avgWait = 0;     // the average wait for a certain Job
  int m = 0;              // length of backup array
  int i, j = 0, n = 1;    // loop variables


  // check command line for correct number of arguments
  if( argc!= 2 ){
    printf("Usage: %s <input file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // open input file for reading
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // create output files for writing
   trcName = argv[1];
   rptName = malloc(256*4);
   strcpy(rptName, argv[1]);
   trcName = strcat(trcName, ".trc");
   rptName = strcat(rptName, ".rpt");
   trc = fopen(trcName, "wb");
   rpt = fopen(rptName, "wb");

   // initialize backup array
   backup = malloc(256*4);
   assert( backup!=NULL );
   fscanf(in, "%d", &m);        // set m to first integer in the input file
   for(i = 0; i < m; i++){
     backup[i] = getJob(in);
   }

   // trace file header
   fprintf(trc, "Trace file: %s\n", trcName);
   fprintf(trc, "%d Jobs:\n", m);
   for(i = 0; i < m; i++){
     printJob(trc, backup[i]);
   }
   fprintf(trc, "\n");

   // report file header
   fprintf(rpt, "Report file: %s\n", rptName);
   fprintf(rpt, "%d Jobs:\n", m);
   for(i = 0; i < m; i++){
     printJob(rpt, backup[i]);
   }
   fprintf(rpt, "\n");
   fprintf(rpt, "***********************************************************\n");

   // run simulation for n processors until n = m-1
   while( n < m ){
     time = 0;
     totalWait = 0;
     maxWait = 0;
     avgWait = 0;

     // trace file output
     fprintf(trc, "\n");
     fprintf(trc, "***********************************************************\n");
     if(n == 1){
       fprintf(trc, "1 processor:\n");
     }
     else{
       fprintf(trc, "%d processors:\n", n);
     }
     fprintf(trc, "***********************************************************\n");

     // initialize queue array
      queue = malloc(256);
      assert( queue!=NULL );
      for(i = 0; i < m; i++){
        queue[i] = malloc(256);
        assert( queue[i]!=NULL );
        queue[i] = newIntegerQueue();
      }

     // set storage array to the indices of their corresponding Jobs
     for(i = 0; i < m; i++){
       enqueue(queue[0], i);
     }

     // trace file output for time = 0
     fprintf(trc, "time=0\n");
     for(i = 0; i <= n; i++){
       fprintf(trc, "%d: ", i);
       if( i == 0 ){
         for(j = 0; j < length(queue[0]); j++){
           printJob(trc, backup[j]);
           queueElement = dequeue(queue[i]);
           enqueue(queue[i], queueElement);
         }
       }
       fprintf(trc, "\n");
     }

     // process all Jobs in this simulation
     while( (length(queue[0])!=m) || (getFinish(backup[peek(queue[0])]) == UNDEF) ){
       int completeJob = 0;
       int minLength = 10;
       int nextProcessor = 1;
       int isChanged = 1;
       //int toProcessIndex = 0;

       // update time and check for any finish or arrival events
       time++;
          i = 1;
          while(i < m){
            // process any Jobs that finish now
            if( (isEmpty(queue[i]) == 0) ){
              if( getFinish(backup[peek(queue[i])]) == time ){
                completeJob = dequeue(queue[i]);
                enqueue(queue[0], completeJob);
                isChanged = 0;
              }
            }
          i++;
          }

          for(i = 0; i < m; i++){

            // process any Jobs that arrive now
            if( getArrival(backup[i]) == time ){
              for(j = 1; j <=n; j++){
                if( (length(queue[j]) < minLength) ){
                  minLength = length(queue[j])+1;
                  nextProcessor = j;
                }
              }
                if( (isEmpty(queue[0]) == 0) ){
                  completeJob = dequeue(queue[0]);
                  enqueue(queue[nextProcessor], completeJob);
                  isChanged = 0;
                }
              }
            }

            // compute finish time
            for(i = 1; i <= n; i++){
              if( isEmpty(queue[i]) == 0 ){
                if( getFinish(backup[peek(queue[i])]) == UNDEF ){
                  computeFinishTime(backup[peek(queue[i])], time);
                  totalWait += getWaitTime(backup[peek(queue[i])]);
                  if( getWaitTime(backup[peek(queue[i])]) > maxWait ){
                    maxWait = getWaitTime(backup[peek(queue[i])]);
                  }
                }
              }
            }

            // trace file output
            if(isChanged == 0){
              fprintf(trc, "\n");
              fprintf(trc, "time=%d\n", time);
              for(i = 0; i <= n; i++){
                fprintf(trc, "%d: ", i);
                for(j = 0; j < length(queue[i]); j++){
                  printJob(trc, backup[peek(queue[i])]);
                  queueElement = dequeue(queue[i]);
                  enqueue(queue[i], queueElement);
                }
                fprintf(trc, "\n");
              }
            }
          }

         // report file output
         avgWait = (double)totalWait/m;
         if(n == 1){
           fprintf(rpt, "1 processor: totalWait=%d, maxWait=%d, averageWait=%.2f\n", totalWait, maxWait, avgWait);
         }
         else{
           fprintf(rpt, "%d processors: totalWait=%d, maxWait=%d, averageWait=%.2f\n", n, totalWait, maxWait, avgWait);
         }

         for(i = 0; i < m; i++){
           resetFinishTime(backup[i]);

         }

         // free heap memory
         for(i = 0; i < m; i++){
           freeIntegerQueue(queue);
         }
         free(queue);
         n++;
         }

         // free backup array
         free(backup);

         //free rptName
         free(rptName);

         // close input and output files
         fclose(in);
         fclose(trc);
         fclose(rpt);

         return EXIT_SUCCESS;
     }
