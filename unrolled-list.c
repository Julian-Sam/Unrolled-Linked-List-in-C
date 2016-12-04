#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "unrolled-list.h"
#include <stdbool.h>


// Makes a generic node
// ull* list is passed in to determine slotsPerNode to malloc
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

  return first;
}


// New unrolled linked list.
// pass in size for slots per node.
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

  return new;
}


// Find the last node and find nextAvailSpot in the array. Insert in this node.
// If the next spot updates to a size greater than the limit, then we reset
// and create a new node.
ull* insert_unrolled(elem e, ull* list)
{
    if (list == NULL)
    {
      fprintf(stderr, "NULL List given to insert\n");
      return NULL;
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

// Check if two elements are equal. Function provided by the client.
bool unrolled_equality(elem1, elem2)
{
  return true;
}

bool isLastElem(ull* list, node* nodeOfElem, size_t numOfElem)
{


}

node* findSecondLastTail(ull* list)
{

}

elem findLastElem(ull* list)
{
  
}

// A quick delete that does not preserve ordering of inserts.
// Deltees the element from the array and replaces it with the last element of
// the list.
ull* quick_delete_unrolled(elem e, ull* list)
{
  node* i;
  node* nodeOfElem;

  size_t j;
  size_t numOfElem;

  bool stop = false;

  // Find the element to delete, go thru each node and each array to search.
  for (i = list->head; i != NULL && !stop ; i = i->next) {
    for (j = 0; j < list->slotsPerNode && !stop; j++) {
      if (unrolled_equality(i->data[j],e)) {
        nodeOfElem = i;
        numOfElem = j;
        stop = true;
      }
    }
  }
  if (stop == false) {
    fprintf(stderr, "Element not found in list to delete\n");
    return NULL;
  }

  // If element is the last element, just delete
  if (!isLastElem(list,nodeOfElem,numOfElem))
    nodeOfElem->data[numOfElem] = findLastElem(list);

  list->totalElems--;
  list->nextAvailSpot--;

  // In case we delete the first element of the last node, need to roll back
  if (list->nextAvailSpot < 0)
  {
    list->nextAvailSpot = slotsPerNode - 1;
    node* oldTail = list->tail;
    list->tail = findSecondLastTail(list);
    free(oldTail);
    list->numNodes--;
  }

  return list;
}

// Return size of the unrolled linked list (total elements in the list)
size_t getSize_unrolled(ull* list)
{
  return list->totalElems;
}


// Standard free function. First frees each array, and then frees the
void free_unrolled(ull* list)
{
  if (list == NULL)
  {
    fprintf(stderr, "NULL List given to free\n");
    return;
  }
  node* i;
  node* j;

  for (i = list->head; i != NULL ; i = i->next) {
    free(i->data); // Free the array
    j = i;
    i = i->next;
    free(j);    // Free the current struct
  }

  free(list); // Free the list header struct
  return;
}

int main()
{
  return 0;
}
