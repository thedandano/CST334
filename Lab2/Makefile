# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file
lab2: lab2.o
	gcc lab2.o -o lab2

# set up dependencies for header files
printf.o: stdio.h
stderr.o: stdio.h
pid_t.o: sys/types.h
fork.o: unistd.h
execlp.o: unistd.h
atoi.o: stdlib.h
errno.o: errno.h

# clean directory
clean:
	rm -f *.o lab2