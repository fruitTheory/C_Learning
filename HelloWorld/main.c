#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTION_CREATE_BOOK 0
#define OPTION_READ_BOOK 1
#define OPTION_LIST_BOOK 2

struct book {
    char title[20];
    char description[200];
};

// global var file
FILE* file;

int handle_create(){

    // variable of type struct book
    struct book b;
    memset(&b, 0, sizeof(b)); // set unused memory to 0
    printf("Enter the books name: ");
    fgets(b.title, sizeof(b.title), stdin); // user input book title
    printf("Book name: %s\n", b.title);

    printf("Enter the books description: ");
    fgets(b.description, sizeof(b.description), stdin); // user input book desc
    printf("Book description: %s\n", b.description);

    // file instance
    file = fopen("./data.bin", "rb+");
    fseek(file, 0, SEEK_END);
    fwrite(&b, sizeof(b), 1, file);
    
} 

int handle_list(){

    // book instance
    struct book b;
    // variable of type FILE
    file = fopen("./data.bin", "rb+");
    // seek back to beginning
    fseek(file, 0, SEEK_SET);

    int index = 0;
    
    while(fread(&b, sizeof(b), 1, file) == 1){
        printf("%i %s\n", index, b.title);
        printf("%s\n", b.description);
        index++;
    }

}


int choose_option(){
    
    printf("Enter an option: ");
    int option = 0;
    scanf("%i", &option);
    getchar();

    int res = 0;
    switch(option){
        case OPTION_CREATE_BOOK:
            handle_create();
            if (res < 0){
                return -1;
            }
            break;

        case OPTION_READ_BOOK:
            printf("Selected to read a book");
            break;

        case OPTION_LIST_BOOK:
            handle_list();
            break;

        default:
            printf("Invalid option");
            return -1;
    }

    return 0;
}


int setup_file(){

    // rb opens knowing its a binary file 
    file = fopen("./data.bin", "rb+");
    if(!file){
        printf("Failed to open file");
        return -1;
    }

    return 0;
}

int main(int argc, char** argv){
    
    if(setup_file() < 0){
        printf("setup failed to initialize");
        return -1;
    }

    if(choose_option() < 0){
        return -1;
    }

    return 0;
}


