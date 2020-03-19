# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3b
lab3b: lab3b.o
	gcc lab3b.o -o lab3b

# set up dependencies for header files
fork.o: unistd.h


# clean directory
clean:
	rm -f *.o lab3b 