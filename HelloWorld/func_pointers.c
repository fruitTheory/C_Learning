#include <stdio.h>

void myFunc(){
    printf("Hello World!\n");
}

void testFunc(){
    printf("Test function\n");
}

int mySum(int a, int b){
    return a+b;
}
int main(int argc, char** argv){

    // Function pointers have return type, variable name, and can take arguements - reference func memory location
    void(*myPtr)() = &testFunc;
    myPtr();

    int(*ptr)(int, int) = &mySum;
    int result = mySum(4, 5);
    printf("%i", result);

    return 0;
}