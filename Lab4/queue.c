#include <stdio.h>
#include "queue.h"
#include <stdlib.h>

//new queue dynamically allocated
struct queue *queue_create() {
   struct queue *q = (struct queue*) malloc(sizeof(struct queue));
   q->front = NULL;
   q->back = NULL;
   return q;
}

//new node insert after last node
struct node* enqueue(struct queue *q, int data){
   struct node *n = node_create(data);

   if(q->front == NULL){ //empty queue; will only run the first time
      q->front = n;
      q->front->next = NULL; // gets data from front and sets next to null because there is nothing after
      q->back = q->front;
      q->back->next = NULL;
   }
   else{ //queue not empty
      q->back->next = n; // checks the end of the queue and send to next then to n; adding to back of queue
      q->back = q->back->next; // sets the new end of the list
      q->back->next = NULL; // last next is a null
   }

   return n;   //returns the node
}

// new node inserted at the front of queue
struct node *queue_add_front(struct queue *q, int data){
   struct node *n = node_create(data);
   struct node* temp = q->front;

   if(q->front == NULL){
      q->front = n;
      q->front->next = NULL;
      q->back = q->front;
      q->back->next = NULL;
   }
   else{
      q->front = n;
      q->front->next = temp;
   }
   return n;
}

// finds the node with given string value
struct node* queue_find(struct queue *q, int data){
   int find = 0;
   struct node* n = q->front;

   while(n != NULL){
      if(n->data == data){
         find = 1;
         break;
      }
      n = n->next; //move on to the next node
   }
   if(!find)
   return NULL;

   return n;
}

// destroy node to free up memory
void queue_destroy(struct queue *q){
   struct node* n = q->front;

   if(q->front == NULL){ //empty queue
      if(q != NULL)

      free(q);

      return;
   }
   while(n != NULL){
      q->front = n->next; //moving the front to the next node
      if(n != NULL)
      node_destroy(n); //deletes the older node
      n = n->next; // moves on to the next node
   }
   if(q->front != NULL)

   exit(1);
   
   q->back = q->front;  //end of nodes set to null

   free(q); //structure cleared
}

//traverses the list and will print what is in them
void queue_traverse(struct queue *q){
   struct node *n = q->front; // starts at the beginning of the node 

   if(q->front == NULL)
   printf("Empty List\n");

   int i = 0;
   while(n != NULL){
      printf("%d %d\n", i, n->data);
      n = n->next;
      i++;
   }
}

//returning the number of elements
uint32_t queue_length(struct queue *q){ // uint32_t is numeric int that guarantees 32 bits
   struct node *n = q->front;

   if(q->front == NULL)
   return (uint32_t)0;

   int i= 0;
   while(n != NULL){
      n = n->next;
      i++;
   }

   return (uint32_t)i;
}

// deletes the first node with given string 
void queue_delete(struct queue *q, int data){
   struct node* prev_node = q->front;
   struct node* temp = NULL;
   int find = 0;

   if(prev_node == NULL)
   return;

   if(prev_node != NULL && prev_node->data == data){
      temp = prev_node;
      prev_node = prev_node->next;
      q->front = prev_node;
      if(q->front == NULL)
      q->back = NULL;
   }
   else {
      while(prev_node != NULL){
         if(prev_node->next != NULL){
            if(prev_node->next->data == data){
               temp = prev_node->next;
               if(temp == q->back){
                  q->back = prev_node;
               }
               find = 1;
               break;
            }
         }
         prev_node = prev_node->next;
      }
      if(!find)
      return;
      prev_node->next = prev_node->next->next;
   }
   node_destroy(temp);
}

//deletes first node of queue
void dequeue(struct queue *q){
   struct node* temp = q->front;

   if(q->front == NULL)
   return;

   q->front = q->front->next;
   node_destroy(temp);
}

