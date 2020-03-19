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

int x;
// main function with command-line args passed
int main(int argc, char *argv[]){
   
   if (fork()) {

  x=1;

} else {

  x=2;

}

printf("%d",x);
   return 0;
}
