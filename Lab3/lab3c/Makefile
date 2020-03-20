# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3c
lab3c: lab3c.o
	gcc lab3c.o -o lab3c

# set up dependencies for header files
fork.o: unistd.h


# clean directory
clean:
	rm -f *.o lab3c 