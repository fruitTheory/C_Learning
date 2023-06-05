#include <stdio.h>

int main(int argc, char** argv){
    // little endian machine
    int abcd = 0x41424344;
    char* ptr = (char*) &abcd;

    printf("%c", ptr[0]);

}
