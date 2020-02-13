#-----------------------------------------------------------------------------
#  Makefile for IntegerStackTest.c
#------------------------------------------------------------------------------

IntegerStackTest : IntegerStackTest.o IntegerStack.o
        gcc -o IntegerStackTest IntegerStackTest.o IntegerStack.o

IntegerStackTest.o : IntegerStackTest.c IntegerStack.h
        gcc -c -std=c99 -Wall IntegerStackTest.c

IntegerStack.o : IntegerStack.c IntegerStack.h
        gcc -c -std=c99 -Wall IntegerStack.c

clean :
        rm -f IntegerStackTest IntegerStackTest.o IntegerStack.o

submit :
        submit cse015-pt.f19 lab3 IntegerStack.c IntegerStack.h IntegerStackTest.c Makefile README

check:
        ls /afs/cats.ucsc.edu/class/cse015-pt.f19/lab3/satavila

memcheck: IntegerStackTest
        valgrind --leak-check=full IntegerStackTest 
