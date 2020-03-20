# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3a
lab3a: lab3a.o
	gcc lab3a.o -o lab3a

# set up dependencies for header files
pipe.o: sys/types.h
stdin.o: stdio.h
fork.o: unistd.h
exit.o: stdlib.h
wait.o: sys/wait.h

# clean directory
clean:
	rm -f *.o lab3a 