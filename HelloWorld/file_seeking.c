#include <stdio.h>


int main(int argc, char** argv){

    // load from local directory
    FILE* file = fopen("./write_long.txt", "r");

    // seek at current with offset which is 0
    fseek(file, 0, SEEK_CUR); // SEEK_SET starts at start

    // how much data we passing around
    char buf[20];

    fread(buf, 1, 20, file);

    // adds null terminator manually
    buf[20] = 0;

    // prints 20 characters into our file from position 0
    printf("%s\n", buf);



    // Goes to end of file
    fseek(file, 0, SEEK_END);
    
    // ftell obtains the current value of file position
    unsigned long file_size = ftell(file);
    
    // Goes back to start
    fseek(file, 0, SEEK_SET);

    // Not prints size of file
    printf("%i\n", file_size);

}


