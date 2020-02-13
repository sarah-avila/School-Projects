#-------------------------
# Makefile for nqueens.c
# ------------------------

nqueens: nqueens.o
        gcc -o nqueens nqueens.o

nqueens.o: nqueens.c
        gcc -c -std=c99 -Wall nqueens.c

clean:
        rm -f nqueens nqueens.o

memcheck:
        valgrind --leak-check=full nqueens -v 8
