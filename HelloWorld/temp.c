#include <stdio.h>

int main(int argc, char** argv){

    int abcd = 0x41424344;
    char* ptr = (char*) &abcd;
    
    printf("%c", ptr[1]);

}
