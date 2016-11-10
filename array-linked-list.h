// Client Defined:
// typedef _______ elem;

struct linked_node{
	elem* data;
	struct linked_node* next;
	struct linked_node* prev;
};

typedef struct linked_node node;

struct list{
	size_t length;
	size_t numNodes;
	node* head;
	node* tail;
};



list* newArray(size_t elementsPerNode);

list* insertPos(elem e, list* l);

elem getValueAtPos(size_t i, list* l)

list* deletePos(elem e, list* l);

list* appendArray(list* l1, list* l2);

size_t arraySize(list* l);

void freeArray(list* l);