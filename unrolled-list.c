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

  new->numNodes = 1;
  new->totalElems = 0;
  new->slotsPerNode = slotsPerNode;
  new->nextAvailSpot = 0;
  node* first = makeNewNode(new);

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
bool unrolled_equality(elem elem1,elem elem2)
{
  if (elem1 == elem2)
    return true;
  else
    return false;
}


node* findSecondLastTail(ull* list)
{
  if (list->head == list->tail)
    return list->head;

  node* temp = list->head;
  node* temp1 = list->head->next;
  while (temp != NULL)
  {
    if (temp1 == list->tail)
      return temp;

    temp = temp1;
    temp1 = temp->next;
  }
  return NULL;

}

elem findLastElem(ull* list)
{

  if (list->nextAvailSpot != 0)
  {
    node* F = list->tail;
    return F->data[list->nextAvailSpot-1];
  }

  if (list->nextAvailSpot == 0 && list->tail == list->head)
  {
    fprintf(stderr, "Cannot find last elem in empty list\n");
  }

  node* temp = list->head;
  node* temp1 = list->head->next;
  while (temp != NULL)
  {
    if (temp1 == list->tail)
      return temp->data[list->slotsPerNode-1];

    temp = temp1;
    temp1 = temp->next;

  }

  return list->head->data[0];

}
bool isLastElem(ull* list, node* nodeOfElem, size_t numOfElem)
{
  if (list->nextAvailSpot == 0)
  {
    if (findSecondLastTail(list) == nodeOfElem && numOfElem == list->slotsPerNode - 1)
      return true;
  }
  else
  {
    if (nodeOfElem == list->tail && numOfElem == list->nextAvailSpot - 1)
      return true;
  }
  return false;

}

// A delete that does not preserve ordering of inserts.
// Deletes the element from the array and replaces it with
// the last element of the list.
ull* delete_unrolled(elem e, ull* list)
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

  // If element not the last element, just replace it with last element
  if (!isLastElem(list,nodeOfElem,numOfElem))
    nodeOfElem->data[numOfElem] = findLastElem(list);

  list->totalElems--;
  list->nextAvailSpot--;

  // In case we delete the first element of the last node, need to roll back
  if (list->nextAvailSpot < 0)
  {
    list->nextAvailSpot = list->slotsPerNode - 1;
    node* oldTail = list->tail;
    list->tail = findSecondLastTail(list);
    list->tail->next = NULL;
    free(oldTail->data);
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

size_t getNumNodes_unrolled(ull* list)
{
  return list->numNodes;
}

void printList(ull* list)
{
  node* i;
  size_t j;
  for (i = list->head; i != NULL; i = i->next) {
    for (j = 0; (i == list->tail && j < list->nextAvailSpot)
                      || (i != list->tail && j < list->slotsPerNode); j++) {
        printf("%d\n",i->data[j]);
    }
  }
}


// Standard free function. First frees each array, and then frees the
void free_unrolled(ull* list)
{
  if (list == NULL)
  {
    fprintf(stderr, "NULL List given to free\n");
    return;
  }

  node* i = list->head;
  node* j;

  while (i != NULL)
  {
      free(i->data); // free the array in the node
      j = i;
      i = i->next;
      free(j); // free the struct itself
  }


  free(list); // Free the list header struct
  return;
}

int main()
{
  ull* new = new_unrolled(1);


  insert_unrolled(1, new);
  insert_unrolled(2, new);
  insert_unrolled(3, new);
  insert_unrolled(4, new);
  insert_unrolled(5, new);
  insert_unrolled(6, new);
  insert_unrolled(7, new);



  printList(new);
  free_unrolled(new);
  return 0;
}
