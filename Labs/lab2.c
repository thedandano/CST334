/*************************************************************
 * @author Ricardo Barbosa 
 * @version 03/13/2020
 * 
 * A C program that uses processes such as fork() and wait()
 * ***********************************************************/

#include <stdio.h>         // printf, stderr
#include <sys/types.h>     // pid_t
#include <unistd.h>        // fork()
#include <stdlib.h>        // atoi()
#include <errno.h>         // errno

// main function with command-line args passed
int
main(int argc, char*argv[]){
   pid_t pid;
   int i; 
   int n = atoi(argv[1]); // number of milliseconds(n) keyboard delay
   printf("\n Before forking \n");
   pid = fork();

   if(pid){
      //Parent Process
      for (i = 0; i < 100; i++){
         printf("\t \t \t PARENT PROCESS %d \n", i);
         usleep(n); // parent sleeps while child finishes 
      }
   }
   else{
      //Child Process Starts
      for(i = 0; i < 100; i++){
         printf("CHILD PROCESS %d\n", i);
         usleep(n);
      }
   }
   return 0;

}
