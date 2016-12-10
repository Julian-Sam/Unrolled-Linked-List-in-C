/*
 Unrolled Linked list
 Author: Julian Sam
 Usage: Feel free to use however.

 Client Required Functions:
	Equality Function:
		Equality function that returns a bool and takes in two arguments, both
		of type elem. Returns true if argument 1 is equal to argument 2.
		Used for deletion. Pass in pointer to function when making a new list.
		(The new_unrolled function)

	Print Function:
		Optional Printing function. Pass in the pointer to this function when
		calling the printList function. The function returns nothing (a void
		function) and takes in one argument of type elem. It should print the
		element in the format that you require.

	Additional:
		IMPORTANT: Please remember to define the type elem. It is commented out
		below. You can also typedef it in your main C file (before the include).


	IMPLEMENTATION DETAILS:
		This is a Unrolled Linked List. Basically, a linked list, but each
		node of the list is an array of a size that is defined by the client.
		Insertion is O(1), since we store the last node and next spot for insertion.
		Deletion is O(n) in the worst case, since we have to search for the
		element. (where n is the number of elements, not the number of nodes)

		Using such a structure greatly reduces memory overhead, and can be used
		to optimize cache performace (make size of array in a node to the size
		of a cache block).

		A traditional implementation of unrolled linked lists stores each node up
		to 75% and creates a new node.
		We will however, take a more simpler approach and fill up each node before
		making a new node.

		Our insertion inserts to the end of the node.
		The deletion works by replacing the element to delete with the last element.

		Deletion is rather expensive. Insertion is not.
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Client Defined:
// typedef _______ elem;


// Structure for each node of the list
struct linked_node{
	elem* data; // Array to store elements.
	struct linked_node* next; // Pointer to next node
};

typedef struct linked_node node;

// Client provided equality function.
typedef bool equiv(elem x, elem y);
// Client provided print function.
typedef void printElem(elem x);

// Our main header structure.
struct unrolled_list{
	int nextAvailSpot; // Next spot in an array to insert element.
	size_t numNodes; // Number of nodes in the list
	size_t totalElems; // Total number of elements in all arrays of all nodes.
	size_t slotsPerNode; // User defined size of each node's array
	node* head; // Head of the list
	node* tail; // Tail of the list
	equiv* equality; // Pointer to the equality function.
};

typedef struct unrolled_list ull;


/*
REQUIRES: A valid equality function.
ENSURES: A new list and an empty node is created.
*/
ull* new_unrolled(size_t slotsPerNode, equiv* equal);

/*
REQUIRES: list is a valid unrolled linkekd list.
ENSURES: Returns true if and only if e is in list
*/
bool lookup(elem e, ull* list);

/*
REQUIRES: list is a valid unrolled linkekd list.
ENSURES: lookup(e) == true.
*/
ull* insert_unrolled(elem e, ull* list);

/*
REQUIRES: list is a valid unrolled linkekd list.
ENSURES: deletes the first instance of e from the list
*/
ull* delete_unrolled(elem e, ull* list);


/*
REQUIRES: list is a valid unrolled linkekd list.
ENSURES: Returns the number of (Elements inserted - Elements deleted)
*/
size_t getSize_unrolled(ull* list);


/*
REQUIRES: list is a valid unrolled linkekd list.
ENSURES: Returns the number of nodes in the list.
*/
size_t getNumNodes_unrolled(ull* list);


/*
REQUIRES: A valid printing function and a valid list.
ENSURES: All elements are printed to the screen in format of the print function
*/
void printList(ull* list, printElem* printFunction);


/*
REQUIRES: A valid list.
ENSURES: All memory used by list is freed
*/
void free_unrolled(ull* list);
