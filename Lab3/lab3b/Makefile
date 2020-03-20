# -*- Makefile -*-

# suffix rule
.c.o: 
	gcc -c $*.c

# set up dependency for main file lab3b
lab3b: lab3b.o
	gcc lab3b.o -o lab3b

# set up dependencies for header files
pipe.o: sys/types.h
stdin.o: stdio.h
fork.o: unistd.h
exit.o: stdlib.h
wait.o: sys/wait.h
write.o: string.h

# clean directory
clean:
	rm -f *.o lab3b 