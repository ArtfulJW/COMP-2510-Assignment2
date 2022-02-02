#include <stdio.h>
#include <strings.h>

// Calculate Length of String
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
        printf("Opening File...\n");
        ifptr = fopen("input.txt","r");

        // Copy File Contents
        printf("Copying File...\n");
        copyFromFile(ifptr, dest_array);

        // Print String
        printf("%s\n", dest_array);

        // Calculate Length
        int x = calcLength((char *) dest_array);
        printf("Length of String: %d\n", x);

        // Close File
        printf("Closing File...\n");
        fclose(ifptr);

    }
    // More than 1 Argument Given.
    else if (argc > 2){
        printf("Error: More than 1 Argument given.\n");
    }

}

int main(int argc, char *argv[]) {

    // NO OPENING FILE IN MAIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // NO IF STATEMENT TO CHECK NUMBER OF ARGUMENTS!!!!!!!!!!!
    // ONLY METHOD CALLS IN MAIN

    FILE *ifptr = {0};
    char *output[500];

    openFile(ifptr, argc, argv, (char *) output);

    return 0;
}
