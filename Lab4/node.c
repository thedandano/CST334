#include <stdio.h>
#include "node.h"
#include <stdlib.h>

struct node *node_create(int data)
{
   struct node *nd = (struct node *)malloc(sizeof(struct node));
   nd->data = data;
   nd->next = NULL;
   return nd;
}

void node_destroy(struct node *n)
{
   free(n); //deletes the entire node
}


