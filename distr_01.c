#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct node{
    struct node* left;
    struct node* right;
	void* data_ptr;
} node_t;

typedef struct list{
	int(*compare)(void*, void*);
	node_t* head;
} list_t;

list_t* create_list(int(*comp)(void*, void*))
{
	list_t* l = (list_t*)malloc(sizeof(list_t));
	l->compare = comp;
	l->head = NULL;
    printf("a list is created\n");
    return l;
}

void delete_list(list_t* list){
    if(list == NULL) { 
        printf("an attempt to delete a not initialized list\n");    
        return;
    }
    if(list->head == NULL) { 
        printf("deleting an empty list\n");
        free(list);
        return;
    }
    printf("deleting the list:\n");
    node_t* temp = NULL;
    while(list->head != NULL){
        temp = list->head;
        list->head = list->head->right;
        printf("deleting element at address: %p\n", temp);
        free(temp);
    }
}

int is_empty(list_t* list){
    if(list == NULL || list->compare == NULL){ 
       printf("list not even initialized\n");
       return -1;
    }
    if(list->head == NULL) { 
        printf("list initialized, but empty\n");
        return 1;
    }
    else{
        printf("list is not empty\n");
        return 0;
    }
}

int compare_strings( void* s1,  void* s2){
	return strcmp((const char*)s1, (const char*)s2); 
}

void update_head(list_t* list){
    while(list->head->left != NULL ){
        list->head = list->head->left; 
    }
    return;
}

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

void print_list(list_t* list){
    node_t* iter = list->head;
    int i = 0;
    printf("content of the list:\n");
    while(iter != NULL){
        printf("element %d: %p\n", ++i, iter->data_ptr);
        iter = iter->right;  
    }
}

int main(int argc, const char** argv){
	list_t* lis = NULL;
    //is_empty(l);
    lis = create_list(compare_strings);

    char* sas = "dsf";
    char* mam = "xdf";
    char* dad = "aaa";
    char* zaz = "aax";

    insert_to_list(lis, sas);
    //print_list(lis);
    insert_to_list(lis, mam);
    //print_list(lis);
    insert_to_list(lis, dad);
    //print_list(lis);
    insert_to_list(lis, zaz);
    //print_list(lis);

    //insert_to_list(l, "world!\n");


    delete_list(lis);
    return 0;
}