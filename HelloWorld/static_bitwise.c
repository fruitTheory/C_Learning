#include <stdio.h>

#define SPECIAL_FLAG 0b00000001

void increment() {
    // interestingly this doesnt reinitialize upon new call
    static int i = 0;
    i++;
    printf("%d\n", i);
}

// with static if this were in another file it would only be availabe in that file 
static int mySum(int a, int b){
    return a + b;
}

int main(int argc, char** argv){

    unsigned char com = 0b11111110;
    if(com | SPECIAL_FLAG){
        printf("flaggy is set\n");
    }
    else{
        printf("flaggy is not set\n");
    }

    unsigned char one = 0b11111110;
    printf("%i\n", ~one);

    // const makes variabls read-only
    const int a = 50;
    int result = mySum(5, 10);
    printf("%i\n", result);

    // Bitwise operation resulting 255
    unsigned char b = 0b11111111;
    unsigned char c = 0b11111111;
    unsigned char b_result = b & c;
    printf("%i\n", b_result);

    increment();
    increment();

}


