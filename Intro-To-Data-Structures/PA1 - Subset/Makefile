#----------------------------
#Makefile for Subset.c
#----------------------------
Subset : Subset.o
        gcc -o Subset Subset.o

Subset.o : Subset.c
        gcc -c -std=c99 -Wall Subset.c

clean :
        rm -f Subset Subset.o

submit:
        submit cse015-pt.f19 pa1 Subset.c Makefile README

check:
        ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/pa1/satavila
~                                                                 
