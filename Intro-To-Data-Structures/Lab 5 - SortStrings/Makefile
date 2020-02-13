#------------------------------------------------------------------------------
# Makefile for SortStrings.c
#------------------------------------------------------------------------------

PROGRAM_NAME = SortStrings
FLAGS        = -std=c99 -Wall
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)

$(EXEBIN) : $(OBJECT)
	gcc -o $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	gcc -c $(FLAGS) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

submit :
        submit cse015-pt.f19 lab5 SortStrings.c Makefile README

check :
        ls /afs/cats.ucsc.edu/class/cse015-pt.f19/lab5/satavila

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) in out
