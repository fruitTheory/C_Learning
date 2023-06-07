#include <stdio.h>
#include <string.h>
#define SPACE " "

int main(int argc, char **argv)
{

    // load from local directory
    FILE *file = fopen("./write_long.txt", "r");

    // seek at current with offset which is 0
    fseek(file, 0, SEEK_CUR); // SEEK_SET starts at start

    // how much data we passing around
    char buf[33];

    fread(buf, 1, 33, file);

    // adds null terminator manually
    // buf[33] = 0;

    // prints 20 characters into our file from position 0
    printf("%s\n", buf);


    // --------------test---------------------

    FILE *file_plus = fopen("./write_plus.txt", "a");
    fseek(file_plus, 0, SEEK_END);

    char app[33];
    char app_spaced[34] = SPACE;
    strcpy(app, buf);
    strcat(app_spaced, app);

    fwrite(app_spaced, 1, strlen(app_spaced), file_plus);

    // --------------test-------------------


    // Goes to end of file
    fseek(file, 0, SEEK_END);

    // ftell obtains the current value of file position
    unsigned long file_size = ftell(file);

    // Goes back to start
    fseek(file, 0, SEEK_SET);

    // Not prints size of file
    printf("%i\n", file_size);
}
