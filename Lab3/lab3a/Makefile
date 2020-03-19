# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3a
lab3a: lab3a.o
	gcc lab3a.o -o lab3a

# set up dependencies for header files
fork.o: unistd.h


# clean directory
clean:
	rm -f *.o lab3a 