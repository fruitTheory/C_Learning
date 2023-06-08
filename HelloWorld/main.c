#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTION_CREATE_BOOK 0
#define OPTION_READ_BOOK 1
#define OPTION_LIST_BOOK 2

struct book
{
    char title[20];
    char description[200];
};

// global var file
FILE *file = NULL;
struct book *bookptr = NULL;

int handle_create()
{

    // variable of type struct book
    struct book b;
    memset(&b, 0, sizeof(b)); // set unused memory to 0

    printf("Enter the books name: ");
    fgets(b.title, sizeof(b.title), stdin); // user input book title
    printf("Book name: %s\n", b.title);

    printf("Enter the books description: ");
    fgets(b.description, sizeof(b.description), stdin); // user input book desc
    printf("Book description: %s\n", b.description);

    // variable of type FILE
    file = fopen("./data.bin", "rb+");
    fseek(file, 0, SEEK_END);
    fwrite(&b, sizeof(b), 1, file);
}

int book_count()
{
    fseek(file, 0, SEEK_END);
    unsigned long total_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return total_size / sizeof(struct book);
}

void view_book(struct book *book)
{
    printf("Description: %s\n", book->description);
    printf("Title: %s\n", book->title);
    
}

int handle_list()
{

    // create variable of type struct book
    struct book b;
    // variable of type FILE
    file = fopen("./data.bin", "rb+");
    // seek back to beginning
    fseek(file, 0, SEEK_SET);
   
    int index = 0;
    int total_books = book_count(); // getting total books from book_count() func
    // creating a new memory of type struct book which is the size of book(220) * total books(3) = 660 bytes
    bookptr = (struct book*)malloc(sizeof(struct book) * total_books);

    // read from file and store in variable b memory location
    while (fread(&b, sizeof(b), 1, file) == 1)
    {
        // copy each book info into our newly created book ptr memory
        memccpy(&bookptr[index], &b, 0, sizeof(b));
        printf("%i - %s\n", index, b.title);
        printf("%i - %s\n", index, b.description);
        index++;
    }

    int option = 0;
    printf("Choose a book: ");
    // scanf requires address of variables because need to modidy their values
    scanf("%i", &option);
    getchar();
    //printf("\n");
    if (option < 0 || option >= total_books)
    {
        printf("Invalid book! Please choose a book:\n\n");
        handle_list();
        // return -1;
    }
    
    view_book(&bookptr[option]);
}

int choose_option()
{

    printf("Enter an option: ");
    int option = 0;
    scanf("%i", &option);
    getchar();

    int res = 0;
    switch (option)
    {
    case OPTION_CREATE_BOOK:
        handle_create();
        if (res < 0)
        {
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
        printf("Invalid option!\n\n");
        choose_option();
        // return -1;
    }

    return 0;
}

int setup_file()
{

    // rb opens knowing its a binary file
    file = fopen("./data.bin", "rb+");
    if (!file)
    {
        printf("Failed to open file");
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{

    if (setup_file() < 0)
    {
        printf("setup failed to initialize");
        return -1;
    }

    if (choose_option() < 0)
    {
        return -1;
    }

    return 0;
}
