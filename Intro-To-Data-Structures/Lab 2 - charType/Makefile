#----------------------------
# Makefile for charType.c
# ---------------------------

charType: charType.o
        gcc -o charType charType.o

charType.o: charType.c
        gcc -c -std=c99 -Wall charType.c

clean:
         rm -f charType charType.o

submit:
        submit cse015-pt.f19 lab2 charType.c Makefile README

check:
        ls /afs/cats.ucsc.edu/class/cse015-pt.f19/lab2/satavila

memcheck:
        valgrind --leak-check=full charType in out
~                                                    
