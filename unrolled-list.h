// Client Defined:
// typedef _______ elem;
typedef int elem;

struct linked_node{
	elem* data;
	struct linked_node* next;
};

typedef struct linked_node node;

struct unrolled_list{
	int nextAvailSpot;
	size_t numNodes;
	size_t totalElems;
	size_t slotsPerNode;
	node* head;
	node* tail;
};

typedef struct unrolled_list ull;


ull* new_unrolled(size_t slotsPerNode);

ull* insert_unrolled(elem e, ull* list);

ull* delete_unrolled(elem e, ull* list);

ull* append_unrolled(ull* l1, ull* l2);

elem get_ithElem(size_t i, ull* list);

size_t getSize_unrolled(ull* list);

size_t getNumNodes_unrolled(ull* list);

void printList(ull* list);

void free_unrolled(ull* list);
