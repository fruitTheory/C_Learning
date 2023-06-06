#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv){
    // stored on stack, limited in size, default: 1 MB (varies)
    int a;
    char b[1024]; // 1 MB on stack

    // example loading a 200mb movie file need to ask for memory aka allocate on heap
    char* ptr = (char*)malloc(1024);
    ptr[0] = 'A';
    ptr[1] = 'B';
    printf("%c\n", ptr[0]);
    // discard memory, need to return memory
    free(ptr);

    int* ptr2 = (int*)malloc(sizeof(int)); // will replace sizeof(int) with 4
    *ptr2 = 50;
    printf("%i\n", ptr2); // prints leftover memory
    printf("%i\n", *ptr2); // prints 50
    free(ptr2);
    
    // goto label
    goto out;
    printf("Yo print me!");

    out:
        printf("Nope, we out!");
        return 0;
}