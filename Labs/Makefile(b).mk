# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file
lab2(b): lab2(b).o
	gcc lab2(b).o -o lab2(b)

# set up dependencies for header files
printf.o: stdio.h
stderr.o: stdio.h
pid_t.o: sys/types.h
execlp.o: unistd.h
atoi.o: stdlib.h
errno.o: errno.h

# clean directory
clean:
	rm -f *.o lab2(b)