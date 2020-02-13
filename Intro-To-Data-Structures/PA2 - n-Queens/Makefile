#-------------------------
# Makefile for Queens.c
# ------------------------

Queens: Queens.o
        gcc -o Queens Queens.o

Queens.o: Queens.c
        gcc -c -std=c99 -Wall Queens.c

clean:
        rm -f Queens Queens.o

submit:
        submit cse015-pt.f19 pa2 Queens.c Makefile README

check:
        ls /afs/cats.ucsc.edu/class/cse015-pt.f19/pa2/satavila

memcheck:
        valgrind --leak-check=full Queens -v 8
