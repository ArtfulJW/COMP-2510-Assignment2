#include <stdio.h>
#include <strings.h>

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

int main(int argc, char *argv[]) {

    FILE *ifptr = {0};
    char *output[500];

    // NO OPENING FILE IN MAIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // NO IF STATEMENT TO CHECK NUMBER OF ARGUMENTS!!!!!!!!!!!
    // ONLY METHOD CALLS IN MAIN

    // Check if one command line argument given.
    if (argc == 2){
        printf("1 Argument Given: [%s]\n", argv[1]);

        // Assign FILE.
        ifptr = fopen("input.txt","r");

        // Copy from FILE to Array.
        copyFromFile(ifptr, (char *) output);

        printf("%s", output);

        for (int x = 0; x < 60; x++){
            //("|%s|\n", output[x]);

        }

        // Close FILE
        fclose(ifptr);

    }
    // More than 1 Argument Given.
    if (argc > 2){
        printf("Error: More than 1 Argument given.\n");
    }
    printf("\nHello, World!\n");
    fclose(ifptr);
    return 0;
}
