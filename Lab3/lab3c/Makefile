# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3c
lab3c: lab3c.o
	gcc lab3c.o -o lab3c

# set up dependencies for header files
pipe.o: sys/types.h
stdin.o: stdio.h
fork.o: unistd.h
exit.o: stdlib.h
wait.o: sys/wait.h

# clean directory
clean:
	rm -f *.o lab3c 