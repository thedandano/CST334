/********************************************************************************
 * @author Ricardo Barbosa 
 * @version March 19, 2020
 * @Title: Lab 3 Part 3
 * Lab3c: The use of pipes was used to implement a Unix command into C; 
 * specifically cat /etc/passwd | grep root
 * 
 ********************************************************************************/

#include <sys/types.h>  // Library for IPC, pipe
#include <sys/ipc.h>    // Library for IPC, pipe
#include <stdio.h>      // stdin, stdout
#include <unistd.h>     // open, fork, execlp, dup2
#include <stdlib.h>     // exit
#include <sys/wait.h>   // wait

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