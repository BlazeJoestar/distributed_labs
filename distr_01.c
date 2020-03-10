#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

// used to generate our main structure - demands 2 function pointers
list_t* create_list(int(*comp)(void*, void*), void(*prt)(node_t*))
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
    list->compare = comp;
    list->print = prt;
	list->head = NULL;
    printf("\na list is created\n");
    return list;
}

// after deletion/addition of a node, we need to make sure
// we have our head pointer pointing to the "far-left" (tfuu) element
void update_head(list_t* list){
    while(list->head->left != NULL ){
        list->head = list->head->left; 
    }
}

// function dedicated to strings only - returns <0 if left if:
// "the first character that does not match has a lower value
//  in ptr1 than in ptr2" 
//          ~ http://www.cplusplus.com/reference/cstring/strcmp/ 
int compare_strings( void* s1,  void* s2){
	return strcmp((const char*)s1, (const char*)s2); 
}

// prints the whole list - dedicated to string type
void print_strings(node_t* iter){
    int i = 0;
    printf("\ncontent of the list:\n");
    while(iter != NULL){
        printf("element %d: %s   | address: %p\n", ++i, (char*)(iter->data_ptr), iter);
        iter = iter->right;
    }
}

// deletes a single element of a list if the given value maches a node
// NOTE: it will remove one node only
void delete_node(list_t* list, void* val){
    if(list == NULL) { 
        printf("\nan attempt to delete a node in a not initialized list\n");    
        return;
    }
    if(list->head == NULL) { 
        printf("\nan attempt to delete a node in an empty list\n");
        return;
    }

    node_t* temp = list->head;
    while(temp != NULL){
        if(list->compare(temp->data_ptr, val) == 0){
            if(temp->left == NULL && temp->right == NULL){
                printf("\ndeleting element at address: %p\nnow list is empty\n", temp);
                free(temp);
                list->head = NULL;
                return;
            }
            if(temp->left != NULL){
                temp->left->right = temp->right;
            }
            if(temp->right != NULL){
                temp->right->left = temp->left;
            }
            list->head = (temp->left == NULL) ? temp->right : temp->left; 
            update_head(list);
            printf("\ndeleting element at address: %p\n", temp);
            free(temp);
            return;
        }
        temp = temp->right;
    }
    printf("\nno such element\n");
}

// deletes the whole list (if it has been initialized/filled)
void delete_list(list_t* list){
    if(list == NULL) { 
        printf("\nan attempt to delete a not initialized list\n");    
        return;
    }
    if(list->head == NULL) { 
        printf("\ndeleting an empty list\n");
        free(list);
        return;
    }
    printf("\ndeleting the list:\n");
    node_t* temp = NULL;
    while(list->head != NULL){
        temp = list->head;
        list->head = list->head->right;
        printf("deleting element at address: %p\n", temp);
        free(temp);
    }
}

// works similarly to strcmp, i.e.
// returns -1 if our list is not initialized
// returns 1 if our list is empty
// returns 0 if our list is not empty
int is_empty(list_t* list){
    if(list == NULL || list->compare == NULL){ 
       printf("\nlist not even initialized\n");
       return -1;
    }
    if(list->head == NULL) { 
        printf("\nlist initialized, but empty\n");
        return 1;
    }
    else{
        printf("\nlist is not empty\n");
        return 0;
    }
}

// adds a single node to our list - it takes into account our compare
// function, so it will make the list ordered
void insert_to_list(list_t* list, void* val){
    if(list->head == NULL){
        list->head = (node_t*)malloc(sizeof(node_t));
        list->head->data_ptr = val;
        list->head->left = NULL;
        list->head->right = NULL;
    }
    else{
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->data_ptr = val;

        node_t* iter = list->head;
        int cmp;
        while(1){
            cmp = list->compare(val, iter->data_ptr);
            if(cmp <= 0){
                if(iter->left != NULL){
                    iter->left->right = temp;
                }
                temp->left = iter->left;
                temp->right = iter;
                iter->left = temp;
                update_head(list);
                return;
            }
            if(iter->right == NULL){
                break;
            }
            iter = iter->right;  
        }
        iter->right = temp;
        temp->left = iter;
        temp->right = NULL;
    }
}


int main(int argc, const char** argv){
	
    list_t* list = create_list(compare_strings, print_strings);

    char* s_1 = "dsf";
    char* s_2 = "xdf";
    char* s_3 = "aaa";
    char* s_4 = "aax";

    insert_to_list(list, s_1);
    insert_to_list(list, s_2);
    insert_to_list(list, s_3);
    insert_to_list(list, s_4);
    
    list->print(list->head);
    
    char* str = NULL;
    
    while(1){
        printf("\n\ninsert element to list (up to 31 characters), or insert \"zmija69\" to exit:\n");
        str = (char*)malloc(32);
        scanf("%s", str);
        if(strcmp(str, "zmija69") == 0){
            break;
        }
        insert_to_list(list, str);
        list->print(list->head);
    }
    list->print(list->head);

    delete_node(list, "dsf");
    delete_node(list, "aaa");
   
    list->print(list->head);

    delete_list(list);
    free(str);
    return 0;
}
