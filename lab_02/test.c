#include <stdio.h>
#include <stdlib.h>
#include "uni_functions.h"

int main(){
    list_t* test = create_list(compare_strings, print_strings);
    char* temp = (char*)malloc(32);
    temp = "askdbkbjdakjbd";
    insert_to_list(test, temp);
    temp = (char*)malloc(32);
    temp = "askdbk";
    insert_to_list(test, temp);
    temp = (char*)malloc(32);
    temp = "as";
    insert_to_list(test, temp);

    test->print(test->head);

    
}