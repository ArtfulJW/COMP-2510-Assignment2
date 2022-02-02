// Preprocessor Directives
#include <stdio.h>
#include <strings.h>

// Macros
#define ROW 100
#define COL 100

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

// Process the words. Seperate into individual words and place each one in an index of a 2D String Array.
void processWords(char *input, int len, char dest_array[ROW][COL]){
    int wordStart = 0;
    int numWord = 0;

    for (int i = 0; i <= len; i++){
        if(input[i] == ' '  || i == len){
            // Iterate through the word.
            for (int y = wordStart; y < i; y++){
                strncat(dest_array[numWord], &input[y],1);
            }
            // End of word
            numWord++;
            // Preparing for next word
            wordStart = i+1;
        }
    }

    // After Loop, Temp will have all the seperate words. To check the 2D Array
    int size = sizeof(dest_array[0])/ sizeof(dest_array[0][0]);
    for (int x = 0 ; x < size; x++){
        printf("%s ", dest_array[x]);
    }

}

// Checks and Opens File
void openFile(FILE *ifptr, int argc, char *argv[], char *dest_array){

    // Check if one command line argument given.
    if (argc == 2){

        char temp[ROW][COL] = {0};

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

        // Seperate the ONE String into Array of Strings. Each index is a word.
        processWords((char *) dest_array, calcLength((char *) dest_array),temp);

        // Close File
        printf("\nClosing File...\n");
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
