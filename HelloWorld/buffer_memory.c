#include <stdio.h>
#include <memory.h>
#include <string.h>

char* hw = "Hello World!";
int main(int argc, char** argv){
    //uninitialized state makes it dangerous to use
    char buf[20];
    // so use ...
    memset(buf, 0, sizeof(buf)); //sizeof buf is 20 bytes and we set all to 0
    // string will look through entire buffer until finding 0, if no 0 it will overflow
    printf("%s\n", buf); // prints null

    // copy 5 bytes into our buffer which represent by 
    memcpy(buf, "Hello", 5); 

    printf("%s\n", buf); // prints Hello

    // copy string into buffer allocate the length of string in mem for it
    memcpy(buf, hw, strlen(hw));

    printf("%s\n", buf); // prints hello world, note memcpy overwrites buffer
    
    // takes first and second import and compares if they match: returns 0
    // returns -1 if first mismatch is less than second mismatch; opposite returns 1
    int result = memcmp("Cello World", "Jello World", strlen("Hello World"));

    printf("%i\n", result);
}