#include <stdio.h>

void myFunc(){
    printf("\nHello World!\n\n");
}

int main(int argc, char** argv){

    myFunc();
    // print number of args then first arg which is program location and any user supplied args
    printf("number of args: %i\narg 0: %s\narg 1: %s\n", argc, argv[0], argv[1]);

    char name[20];
    int age = 0;

    printf("\nYour name: ");
    // gets user input through standard input stream and puts cap on name size
    fgets(name, sizeof(name), stdin);

    printf("Your age: ");
    // store user age at memory location of age variable
    scanf("%i", &age);

    printf("\n");
    printf("Your name is %s", name);
    printf("Your age is %i\n\n", age);
    printf("Your name is located at address %i\n", &name);
    printf("Your age is located at address %i\n\n", &age);

    return 0;
    
}