#include <stdio.h>
#include <memory.h>
#include <string.h>

#define MAX_STRING_LEN 1024

int main(int argc, char** argv){

    /*
    * Setting up reading files
    *
    */
    FILE* f = fopen("./read.txt", "r");
    if(!f){
        printf("Failed open file");
        return -1;
    }

    char buf[20];
    memset(buf, 0, sizeof(buf));

    // read into memory which memory, buffer, element 1 btye 20 elements from FILE f
    int read_result = fread(buf, 1, 20, f);
    // fread _Success_(return != 0)
    if(read_result == 0){
        printf("Problem reading");
        return -1;
    }

    printf("%s\n", buf);
    printf("%i\n", read_result);

    fclose(f);

    /*
    * Setting up writing files
    *
    */
    FILE* fw = fopen("./write.txt", "w");
    if(!fw){
        printf("Failed write file");
        return -1;
    }
    char my_msg[] = "Hello World 2.0\n";
    // buffer, element size, amount of elements, which file
    fwrite(my_msg, 1, strlen(my_msg), fw);

    fclose(fw);

    /*
    * Setting up writing files
    *
    */
    FILE* fa = fopen("./write.txt", "a");
    if(!fa){
        printf("Failed append to file");
        return -1;
    }
    char append_msg[] = "Hello World 2.0 --appended";
    fwrite(append_msg, 1, strlen(append_msg), fa);

    fclose(fa);


    /*
    * Setting up writing+ files
    * This can create a file and can read and write to it
    */
    FILE* fwp = fopen("./write_plus.txt", "w+");
    if(!fwp){
        printf("Failed to write file");
        return -1;
    }
    char write_msg[] = "Hello World 2.0 --written";
    fwrite(write_msg, 1, strlen(write_msg), fwp);

    fclose(fwp);


    char buf2[MAX_STRING_LEN];
    FILE* fwp2 = fopen("./write_plus.txt", "r");
    // fread _Success_(return != 0)
    if(fwp2 != NULL){
        size_t len = fread(buf2, sizeof(char), MAX_STRING_LEN-1, fwp2);
        buf2[len] = '\0';
        printf("%s", buf2);
        fclose(fwp2);
    }
    else{
        printf("Failed to read file");
        return -1;
    }

}