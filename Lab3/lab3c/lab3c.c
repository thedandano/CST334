/********************************************************************************
 * @author Ricardo Barbosa 
 * @version March 19, 2020
 * 
 * Lab3c: 
 * 
 * 
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//main
int
main(int argc, char *argv[]){
   int fds[2];
   pipe(fds); // setting up a pipe 

   //program forks
   //child process created that closes upstream and opens downstream
   //duplicating downstream to stdin
   if(fork() == 0){
      dup2(fds[0],0);   //parent runs 'dup2()' to duplicate it's stdin to the pipe's reader
      close(fds[1]);    // child closes the pipe reader file descriptor
      execlp("grep", "grep", "root", NULL);
      
      exit(0);
   }
   //child process created that opens upstream and closes downstream
   //duplicating upstream to stdout
   else if(fork() == 0){
      dup2(fds[1],1);   
      close(fds[0]);
      execlp("cat", "cat", "/etc/passwd", NULL);
      exit(0);
   }
   else { //parent closes both ends and waits for children
      close (fds[0]); // parent closes the pipe writer file descriptor
      close(fds[1]); // parent closes the pipe reader file descriptor 
      wait(0);
      wait(0);
   }
   return 0;
}