#include <stdio.h>

/**
 * Description of function
 * @param argc does this thing
 * @param argv does this other thing
 * this is great for doxygen expects to stars in front
*/
int add(int a, int b);

int main(int argc, char** argv){
    //bits
    char b = 0b00000011;
    int a = 0x20;
    // print as decimal or hexadecimal
    printf("%i %x %i\n", a, a, b);

    int values = add(40, 50);
    printf("%i", values);
}