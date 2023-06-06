#include <stdio.h>

int main(int argc, char** argv){

    // casting float to int
    float a = 1.5;
    int b = (int)a;
    printf("%f %i\n", a, b);

    // little endian machine - most processors are this - flips bytes, only happen with primitive types
    int abcd = 0x41424344;
    // by casting to char we can output the hex values as if thyre characters
    char* ptr = (char*) &abcd;
    printf("%c\n", ptr[0]); //outputs D
    
    float e = 1.5;
    char f = (char) e;
    printf("%i\n", f);

    char x = 0x46;
    char* ptr2 = (char*)&x;
    // prints memory location, F due to dereference to value, F due to being char value 
    printf("%i %c %c", ptr2, *ptr2, x); 

}
