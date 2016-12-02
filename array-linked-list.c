#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "array-linked-list.h"


ull* new_unrolled(size_t slotsPerNode)
{
  ull* new = malloc(sizeof(ull));
  if (new == NULL)
  {
    fprintf(stderr, "Not enough space for new list. (Malloc failed)\n");
    return NULL;
  }

  node* first = malloc(sizeof(node));
  if (first == NULL)
  {
    fprintf(stderr, "Not enough space for new node. (Malloc failed)\n");
    return NULL;
  }

  first->data = malloc(sizeof(elem)*slotsPerNode);
  first->next = NULL;

  new->numNodes = 0;
  new->totalElems = 0;
  new->slotsPerNode = slotsPerNode;
  new->head = NULL;
  new->tail = NULL;
}

ull* insert_unrolled(elem e, ull* list)
{
    if (list == NULL)
    {
      fprintf(stderr, "NULL List given to insert\n");
      return;
    }
    node* main = list->tail;
    main->data[list->nextAvailSpot] = e;

    return NULL;

}


size_t getSize_unrolled(ull* list)
{
  return list->totalElems;
}

void free_unrolled(ull* list)
{
  if (list == NULL)
  {
    fprintf(stderr, "NULL List given to free\n");
    return;
  }
  node* i;
  for (i = list->head; i != NULL ; i = i->next) {
    free(i->data);
    i = i->next;
  }
  free(list);
  return;
}

int main()
{
  return 0;
}
