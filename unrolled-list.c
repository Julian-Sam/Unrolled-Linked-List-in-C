#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "unrolled-list.h"


node* makeNewNode(ull* list)
{
  node* first = malloc(sizeof(node));
  if (first == NULL)
  {
    fprintf(stderr, "Not enough space for new node. (Malloc failed)\n");
    return NULL;
  }
  first->data = malloc(sizeof(elem)*list->slotsPerNode);
  first->next = NULL;
}

ull* new_unrolled(size_t slotsPerNode)
{
  ull* new = malloc(sizeof(ull));
  if (new == NULL)
  {
    fprintf(stderr, "Not enough space for new list. (Malloc failed)\n");
    return NULL;
  }

  node* first = makeNewNode(new);

  new->numNodes = 1;
  new->totalElems = 0;
  new->slotsPerNode = slotsPerNode;
  new->head = first;
  new->tail = first;
}


ull* insert_unrolled(elem e, ull* list)
{
    if (list == NULL)
    {
      fprintf(stderr, "NULL List given to insert\n");
      return;
    }
    node* tail = list->tail;
    tail->data[list->nextAvailSpot] = e;
    list->nextAvailSpot++;
    list->totalElems++;

    if (list->nextAvailSpot >= list->slotsPerNode)
    {
      list->nextAvailSpot = 0;
      list->numNodes++;
      node* newTail = makeNewNode(list);
      tail->next = newTail;
      list->tail = newTail;
    }


    return list;

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
