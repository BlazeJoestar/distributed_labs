
#include "uni_functions.h"

int main(){

	list_t* test = create_list(compare_strings, print_strings);
	printf(" you will be asked for 3 strings\n"); 
	char* temp = NULL;
	for(int i = 0; i < 3; i ++){
		printf("insert %d. string: ", i+1);
		temp = (char*)malloc(32);
		scanf("%s", temp);
		insert_to_list(test, temp);
	}	
	
	test->print(test->head);
	delete_list(test);
	free(test);
	return 0;    
}
