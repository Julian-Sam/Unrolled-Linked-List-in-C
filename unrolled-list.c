#include "unrolled-list.h"
// Makes a generic node
// The ull* list is passed in to determine slotsPerNode to malloc
// Returns pointer to the new node
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
// Pass in size for slots per node.
ull* new_unrolled(size_t slotsPerNode, equiv* equal)
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



  // Add the equality function the struct for future comparisions.
  if (equal == NULL)
  {
    fprintf(stderr, "NULL given as equality function \n");
    return NULL;
  }

  new->equality = equal;


  return new;
}


// Find the last node and find nextAvailSpot in the array. Insert in this node.
// If the next spot updates to a size greater than the limit, then we reset
// the nextAvailSpot and create a new node.
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

    // In case we need to make new node
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

// Helper function for the delete function. Finds the node before the tail.
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


// Helper function for the delete function. Finds the element at the end.
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
  // Go to end
  while (temp != NULL)
  {
    if (temp1 == list->tail)
      return temp->data[list->slotsPerNode-1];

    temp = temp1;
    temp1 = temp->next;

  }

  return list->head->data[0];

}

// Returns true if the element is the last one in the unrolled linked list
bool isLastElem(ull* list, node* nodeOfElem, size_t numOfElem)
{
  if (list->nextAvailSpot == 0)
  {
    if (findSecondLastTail(list) == nodeOfElem &&
                                    numOfElem == list->slotsPerNode - 1)
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
// the last element of the list. If the element is the last one, then just
// adjust metadata and return.
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
      if ((*list->equality)(i->data[j],e)) {
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

// Return number of nodes.
size_t getNumNodes_unrolled(ull* list)
{
  return list->numNodes;
}

// Print function, Client must pass in a printing function for the element.
void printList(ull* list, printElem* printFunction)
{
  node* i;
  size_t j;
  for (i = list->head; i != NULL; i = i->next) {
    for (j = 0; (i == list->tail && j < list->nextAvailSpot)
                      || (i != list->tail && j < list->slotsPerNode); j++) {
        (*printFunction)(i->data[j]);
    }
  }
}


bool lookup(elem e, ull* list)
{
  node* i;
  size_t j;

  for (i = list->head; i != NULL; i = i->next) {
    for (j = 0; j < list->slotsPerNode; j++) {
      if ((*list->equality)(i->data[j],e)) {
        return true;
      }
    }
  }
  return false;
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
      j = i; // Save the struct itself
      i = i->next; // get the next struct
      free(j); // free the struct itself
  }


  free(list); // Free the list header struct
  return;
}
