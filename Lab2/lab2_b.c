/*************************************************************
 * @author Ricardo Barbosa 
 * @version 03/13/2020
 * 
 * A C program that uses processes such as fork() and wait()
 * ***********************************************************/

#include <stdio.h>         // printf, stderr
#include <sys/types.h>     // pid_t
#include <unistd.h>        // fork, execlp
#include <stdlib.h>        // atoi()
#include <errno.h>         // errno

// main function with command-line args passed
int main(int argc, char *argv[]){
   pid_t pid;
   int i; 
   int n = atoi(argv[1]); // number of milliseconds(n) keyboard delay
   printf("\nBefore forking\n\n");
   pid = fork();
   if(pid == -1) {
      fprintf(stderr, "can't fork, error %d\n", errno);
   }
   if (pid == 0) {
      //Child Process
      execlp("/bin/ls", "ls", NULL); 
   }
   if(pid) {
      //Parent Process
      wait(NULL);
      printf("Child Complete");
      exit(0);
   }
   return 0;
}
