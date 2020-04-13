#include "uni_functions.h"

list_t* create_list(int(*comp)(void*, void*), void(*prt)(node_t*)){
	list_t* list = (list_t*)malloc(sizeof(list_t));
    list->compare = comp;
    list->print = prt;
    list->head = NULL;
    printf("\na list is created\n");
    return list;
}

void update_head(list_t* list){
    while(list->head->left != NULL ){
        list->head = list->head->left; 
    }
}

int compare_strings( void* s1,  void* s2){
	return strcmp((const char*)s1, (const char*)s2); 
}

void print_strings(node_t* iter){
    int i = 0;
    printf("\ncontent of the list:\n");
    while(iter != NULL){
        printf("element %d: %s   | address: %p\n", ++i, (char*)(iter->data_ptr), iter);
        iter = iter->right;
    }
}

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
                free(temp->data_ptr);
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
            free(temp->data_ptr);
	    free(temp);
            return;
        }
        temp = temp->right;
    }
    printf("\nno such element\n");
}

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
        free(temp->data_ptr);
	free(temp);
    }
}

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
