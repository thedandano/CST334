/********************************************************************************
 * @author Ricardo Barbosa 
 * @version March 19, 2020
 * @Title Lab 3 Part 2
 * Lab3b: The use of pipes was implemented to show when the forked call
 * would implement write, and when it would implement read.  The write was performed
 * during upstream and the read was performed during downstream.
 * 
 ***********************************************************************************/


#include <sys/types.h>  // Library for IPC, pipe
#include <sys/ipc.h>    // Library for IPC, pipe
#include <stdio.h>      // stdin, stdout
#include <unistd.h>     // open, fork, execlp, dup2
#include <stdlib.h>     // exit
#include <sys/wait.h>   // wait
#include <string.h>     // write

//main
int
main(int argc, char *argv[]){
   int fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   //child process created that closes upstream and opens downstream
   //duplicating downstream to stdin
   if(fork() == 0){
      printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
      close(fds[0]);
      for(int i=0; i < argc; i++){
         write(fds[1], argv[i], strlen(argv[i]));
      }
      exit(0);
   }
   //child process created that opens upstream and closes downstream
   //duplicating upstream to stdout
   else if(fork() == 0){
      printf("\nReader on the downstream end of the pipe \n");
      close(fds[1]);
      while((count = read(fds[0], buff, 60)) > 0){
         for(i = 0; i < count; i++){
            write (1, buff+i, 1);
            write(1, " ", 1);
         }
         printf("\n");
      }
      exit(0);
   }
   else { //parent closes both ends and waits for children
      close (fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
   return 0;
}