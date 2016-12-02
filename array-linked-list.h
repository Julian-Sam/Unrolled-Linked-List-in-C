// Client Defined:
// typedef _______ elem;
typedef int elem;


struct linked_node{
	elem* data;
	struct linked_node* next;
	// struct linked_node* prev;
};
typedef struct linked_node node;

struct unrolled_list{
	size_t numNodes;
	size_t totalElems;
	size_t nextAvailSpot;
	size_t slotsPerNode;
	node* head;
	node* tail;
};
typedef struct unrolled_list ull;

ull* new_unrolled(size_t slotsPerNode);

ull* insert_unrolled(elem e, ull* l);

elem find_unrolled(size_t i, ull* l);

ull* delete_unrolled(elem e, ull* l);

ull* append_unrolled(ull* l1, ull* l2);

size_t getSize_unrolled(ull* l);

void free_unrolled(ull* l);
