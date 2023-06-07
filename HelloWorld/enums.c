#include <stdio.h>

enum week{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

const char* week_str[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

const char* week_to_str(enum week day){
    return week_str[day];
}

int main(int argc, char** argv){

    int a = (int) Monday;
    printf("%i\n", a);

    // arrays are perfect for enums since both start at 0!
    printf("%s\n", week_to_str(Friday));

    
}


