#include <stdio.h>

#define CASE_1 1

int main(int argc, char** argv){

    {
        int a = 0;
        printf("%i\n", a);
    }
    int a = 1;
    printf("%i\n", a);

    int result = 1;
    switch(result){
        case 0:
            printf("case 0\n");
            break; // without break it will continue on

        case CASE_1:
            printf("case 1\n");
            break; // could combine cases without breaks
        
        case 2:
            //NULL;

        case 3:
            printf("represents case 2 and case 3\n");
            break;

        // default case scenario if variable out of case scope
        default:
            printf("none match\n");

        break;
    }

}


