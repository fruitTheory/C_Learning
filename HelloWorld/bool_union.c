#include <stdio.h>
#include <stdbool.h>

struct testStruct{

    int c;
    union myUnion{
        // unions share same memory region
        int a;
        int b;
};
};

int main(int argc, char** argv){ 
    // in C bool is not a built-in data type
    bool F = false;
    bool T = true;

    union myUnion uni;
    uni.a = 30;
    uni.b = 40;

    printf("%i %i\n", uni.a, uni.b);

    struct testStruct test;
    test.c = 30;
    test.b = 20;
    test.a = 10;

    printf("%i %i %i\n", test.a, test.b, test.c);






    return 0;
}