#include <stdio.h>

int main(int argc, char** argv){

    int i = 0;

    while(i < 10){
    if(i == 5){
        break;
    }
    i++;
    printf("hi %i ", i);

    }
    for(int i=1; i < 11; i++){
        printf("fur %i ", i);

    }
    return 0;
}