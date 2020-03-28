#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    char pageCache[100]; // Cache that holds the input from test file
    int page_in_file = 0; // pages in the accesses.txt file
    int page_fault = 0; // page page_faults accrued
    int page_num = 0; // the page number in accesses.txt file
    int node_total = 0; // the node total in the queue(cache counter)
    struct queue* q = queue_create(); // empty queue
    struct node* temp = NULL;

   node_total = queue_length(q);
    while (fgets(pageCache, 100, stdin)){
    	page_num = atoi(pageCache); // Stores number read from file as an int

         if(node_total < CACHE_SIZE) //cache counter less than cache size: if there is room
         {
            enqueue(q, page_num);
            node_total = queue_length(q);
            page_fault++;
         }
         else{
            temp = NULL;
            temp = queue_find(q, page_num); // if there is no room it will find a node to dequeue
            if(temp == NULL)
            {
               dequeue(q); //remove the found node
               enqueue(q, page_num); //insert the node trying to put in
               page_fault++;
            }
         }
            page_in_file++;
      
    }

    printf("%d Total Page page_faults on %d\n", page_fault, page_in_file);
    return 0;



}