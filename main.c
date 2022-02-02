#include <stdio.h>
#include <strings.h>

int calcLength(char *arr){
    return (int)strlen(arr);
}

// Read from file and dump contents into String Array (dest_array).
void copyFromFile(FILE *ifptr, char* dest_array){

    char str[60];
    char output[6000];

    while (fgets(str, sizeof(str), ifptr) != NULL){
        // Current line contains something - str now contains what FILE has, Concat to output.
        strcat(output, str);
    }

    // Output Now contains Whatever was in FILE.
    strcpy(dest_array, output);
}

// Checks and Opens File
void openFile(FILE *ifptr, int argc, char *argv[], char *dest_array){

    // Check if one command line argument given.
    if (argc == 2){
        printf("1 Argument Given: [%s]\n", argv[1]);

        // Assign FILE.
        ifptr = fopen("input.txt","r");
        copyFromFile(ifptr, dest_array);

    }
    // More than 1 Argument Given.
    if (argc > 2){
        printf("Error: More than 1 Argument given.\n");
    }

}

void closeFile(FILE *ifptr){
    fclose(ifptr);
}

int main(int argc, char *argv[]) {

    // NO OPENING FILE IN MAIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // NO IF STATEMENT TO CHECK NUMBER OF ARGUMENTS!!!!!!!!!!!
    // ONLY METHOD CALLS IN MAIN

    FILE *ifptr = {0};
    char *output[500];

    openFile(ifptr, argc, argv, (char *) output);

    printf("%s", output);

    int x = calcLength((char *) output);
    printf("%d", x);

    closeFile(ifptr);

    return 0;
}
