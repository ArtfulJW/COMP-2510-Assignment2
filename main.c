// Preprocessor Directives
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

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

// Check and replace words
void replaceWord(char inputArr[ROW][COL]) {
    // Boolean to check cases.
    bool start = false;
    bool end = false;
    char target[100];
    char replace[100];
    char temp[100] = {0};
    char zero[100] = {0};
    char *checkReplace = NULL;
    int size = sizeof(inputArr[0])/sizeof(inputArr[0][0]);

    // User Input
    printf("Enter a word to replace:");
    scanf("%s", target);
    printf("Replace %s with:", target);
    scanf("%s", replace);

    // Iterate. Check if word in 2D Array contains 'target'
    for (int i = 0; i < size; i++){

        // Check for word
        checkReplace = strstr(inputArr[i], target);
        if (checkReplace != NULL){

            // 'target' is in the word, thus FOUR cases - target is either at the start, middle, end, or is target already.
            printf("FOUND: '%s', INDEX: %d\n", inputArr[i],i);

            if(inputArr[i][0] == target[0]){
                start = true;
            }
            if(inputArr[i][strlen(inputArr[i])-1] == target[strlen(target)-1]){
                end = true;
            }

            if (start && !end) {
                // target at start
                printf("Target at start\n");
                // Target has been replace
                strcpy(temp,replace);
                // Concate rest of word.
                for(int x = 0; x < strlen(inputArr[i]); x++){
                    if(x >= strlen(target)){
                        strncat(temp,&inputArr[i][x],1);
                    }
                }
                // Overwrite Index with new word
                strcpy(inputArr[i], temp);
            } else if (!start && end) {

                // target at end
                printf("Target at end\n");
                int length = (int)(strlen(inputArr[i]) - strlen(target));
                // Iterate to target
                for (int x = 0; x < length; x++){
                    strncat(temp,&inputArr[i][x],1);
                }
                // Append replace
                strcat(temp,replace);
                // Overwrite Index with new word
                strcpy(inputArr[i], temp);
                // Zero out temp Array
                strcpy(temp,zero);
            } else {
                // target is in middle or word is already target
                if(strlen(target) == strlen(inputArr[i])){
                    printf("Word is target\n");
                    strcpy(inputArr[i],replace);
                } else {
                    printf("Target in middle\n");
                    int startlength = (int)(checkReplace - inputArr[i]);
                    // Iterate to target
                    for (int x = 0; x < startlength; x++){
                        strncat(temp,&inputArr[i][x],1);
                    }
                    // Append Replace
                    strcat(temp,replace);
                    // Concate rest of word.
                    int endlength = (int)(strlen(inputArr[i]) - startlength);
                    for(int x = 0; x < strlen(inputArr[i]); x++){
                        if(x > (startlength + strlen(replace)+1)){
                            strncat(temp,&inputArr[i][x],1);
                        }
                    }
                    // Overwrite Index with new word
                    strcpy(inputArr[i], temp);
                    // Zero out temp Array
                    strcpy(temp,zero);
                }
            }

        }
        checkReplace = NULL;
        start = false;
        end = false;
    }
}

// Process the words. Seperate into individual words and place each one in an index of a 2D String Array.
void processWords(char *input, int len, char dest_array[ROW][COL]){
    int wordStart = 0;
    int numWord = 0;

    for (int i = 0; i <= len; i++){
        if (input[i] == ' '  || i == len || input[i] == '\n'){
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

        if(ifptr == NULL){
            printf("Error, cannot open file.\n");
        } else {

            // Copy File Contents
            printf("Copying File...\n");
            copyFromFile(ifptr, dest_array);

            // Seperate paragraph into Array of Strings. Each index is a word.
            processWords((char *) dest_array, calcLength((char *) dest_array), temp);

            // Iterate and change words according to User Input.
            replaceWord(temp);

            // Close Input File
            printf("\nClosing File...\n");
            fclose(ifptr);

            // Delete Input File
            remove("input.txt");

            // Create new File
            FILE *ofptr = fopen("input.txt", "w");
            // Write Data to File
            int size = sizeof(temp[0]) / sizeof(temp[0][0]);
            for (int y = 0; y < size; y++) {
                fputs(temp[y], ofptr);
                fputs(" ", ofptr);
            }
            fclose(ofptr);
        }
    }
    // More than 1 Argument Given.
    else if (argc > 2){
        printf("Error: More than 1 Argument given.\n");
    }
}

int main(int argc, char *argv[]) {

    FILE *ifptr = {0};
    char *output[500];

    openFile(ifptr, argc, argv, (char *) output);

    return 0;
}
