/********************************************************************************
 * @author Ricardo Barbosa 
 * @version March 19, 2020
 * @Title: Lab 3 Part 3
 * Lab3c: The use of fork pipes was used to implement a Unix command into C; 
 * specifically the ls | more command.
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
main() {
   int fds[2];  // 
   pipe(fds);   //
   //Child 1 duplicates downstream into stdin
   if(fork() == 0){
      dup2(fds[0],0);
      close(fds[1]);
      execlp("more", "more", 0);
   }
   //child 2 duplicates upstream into stdout
   else if (fork() ==0){
      dup2(fds[1], 1);
      close(fds[0]);
      execlp("ls", "ls", 0);
   }
   else { //parent closes both ends and waits for children
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
   return 0;
}