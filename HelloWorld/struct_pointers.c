#include <stdio.h>


struct myStruct{
    // structure that holds
    int a;
    char b;
};

void print_struct(struct myStruct* s){
    // access pointer variables with ->
    printf("%i %c \n", s->a, s->b);
}

int main(int argc, char** argv){
    // instance of myStruct
    struct myStruct s;
    // acccess non pointer variables with a doit
    s.a = 1;
    s.b = 'C';

    // inputs referencing instace of myStructs s memory location
    print_struct(&s);


}