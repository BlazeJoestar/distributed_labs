#ifndef _UNI_FUNCTIONS_
#define _UNI_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uni_types.h"

// used to generate our main structure - demands 2 function pointers
list_t* create_list(int(*comp)(void*, void*), void(*prt)(node_t*));

// after deletion/addition of a node, we need to make sure
// we have our head pointer pointing to the "far-left" (tfuu) element
void update_head(list_t* list);

// used to generate our main structure - demands 2 function pointers
list_t* create_list(int(*comp)(void*, void*), void(*prt)(node_t*));

// after deletion/addition of a node, we need to make sure
// we have our head pointer pointing to the "far-left" (tfuu) element
void update_head(list_t* list);

// function dedicated to strings only - returns <0 if left if:
// "the first character that does not match has a lower value
//  in ptr1 than in ptr2" 
//          ~ http://www.cplusplus.com/reference/cstring/strcmp/ 
int compare_strings( void* s1,  void* s2);

// prints the whole list - dedicated to string type
void print_strings(node_t* iter);

// deletes a single element of a list if the given value maches a node
// NOTE: it will remove one node only
void delete_node(list_t* list, void* val);

// deletes the whole list (if it has been initialized/filled)
void delete_list(list_t* list);

// works similarly to strcmp, i.e.
// returns -1 if our list is not initialized
// returns 1 if our list is empty
// returns 0 if our list is not empty
int is_empty(list_t* list);

// adds a single node to our list - it takes into account our compare
// function, so it will make the list ordered
void insert_to_list(list_t* list, void* val);

#endif
