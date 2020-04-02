#ifndef _UNI_TYPES_
#define _UNI_TYPES_

// a struct capable of storing data of any type
// it is going to be our basic element of doubly linked list list
typedef struct node{
    struct node* left;
    struct node* right;
	void* data_ptr;
} node_t;

// attempt to mimic a generic list
// it needs to have compare and print functions assigned
typedef struct list{
	int(*compare)(void*, void*);
    void(*print)(node_t*);
    node_t* head;
} list_t;

#endif