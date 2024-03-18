#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//work on this one

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);

int bSize;
int done = 0;
int done2 = 0;
int index1 = 0;
int mnTest = 0;

struct letterLocation { // where in array a given letter is found and where in the word it is found
  int row;
  int column;
  int marker;
}; 


int searchAround(char** arr, char* word, struct letterLocation* location, int i, int j, int bSize, int wordLength){
    //printf("index: %d\n", index1);
        if (index1 == wordLength){
            //indicate that word was found!
            return 1;
        }
        //printf("i: %d, j: %d\n", i, j);
        for(int m = i-1; m <= i+1; m++){
            if (m >= 0 && m < bSize ) {
                for(int n = j-1; n <= j+1; n++){

                    // printf("%d \n", n);
                    // if(m != i && n != j){
                    //     mnTest = 1;
                    // }

                    if (n >= 0 && n < bSize /*&& (mnTest == 1)*/){


                        if(m != i || n != j){ // in order to avoid checking the point we are on

                            //printf("m: %d, n: %d\n", m, n);
                            if (*(*(arr + m) + n) == *(word + index1)){

                                (*(location + index1)).row = m;

                                (*(location + index1)).column = n;

                                (*(location + index1)).marker = index1;
                                index1++;
                                //printf("index: %d\n", index1);
                                searchAround(arr, word, location, m, n, bSize, wordLength);
                                if (index1 == wordLength){
                                    return 1;
                                }
                            index1--;
                            }
                        }
                    }
                }
            }
        }

    return 0;
}



int powerofTen(int x){
    int count = 0;
    int tens = 10;
    while (x != 0) {
        x /= 10;
        count++;
    }
    if (count == 1){
        return tens;
    }
    else{
        for (int i = 1; i < count; i++){
            tens *= 10;
        }
    }
    return tens;
}

// Main function, DO NOT MODIFY     
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);

    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);

    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);

    return 0;
}

void printPuzzle(char** arr) {
    // This function will print out the complete puzzle grid (arr)(block). 
    // It must produce the output in the SAME format as the samples in the instructions.

    for(int i = 0; i < bSize; i++) {
        for(int j = 0; j < bSize; j++) {

            printf("%c ", *(*(arr + i)+j)); // print ea char in char array, was read into a 2D array

        }
        printf("\n");
    }

}


void puzzleMap(int** arr, struct letterLocation* location, struct letterLocation* location2, int wordLength){
    // rewrite the array using the points (i,j)

    for (int i = 0; i < bSize; i++) { // set everything else to 0
        for (int j = 0; j < bSize; j++) {
            *(*(arr + i)+j) = 0;
        }
    }
    for (int m = 0; m < wordLength; m++){ // set the points that we do have with the proper indices 
        if (*(*(arr + (*(location + m)).row) + (*(location + m)).column) != 0){ 
            (*(*(arr + (*(location + m)).row) + (*(location + m)).column)) += powerofTen(*(*(arr + (*(location + m)).row) + (*(location + m)).column)) * ((*(location + m)).marker + 1); // marker +1 in parenthesis because order of ops
            // if theres already a number there, add this new one to its left !

        }
        else{
             (*(*(arr + (*(location + m)).row) + (*(location + m)).column)) = (*(location + m)).marker + 1;
             //printf("%d\n", (*(*(arr + (*(location + m)).row) + (*(location + m)).column)));
        }
    }
    if(done2 == 2){
        for (int m = 0; m < wordLength; m++){ // set the points that we do have with the proper indices 
            if (*(*(arr + (*(location2 + m)).row) + (*(location2 + m)).column) != 0){ 
                (*(*(arr + (*(location2 + m)).row) + (*(location2 + m)).column)) += powerofTen(*(*(arr + (*(location2 + m)).row) + (*(location2 + m)).column)) * ((*(location2 + m)).marker + 1); // marker +1 in parenthesis because order of ops
                // if theres already a number there, add this new one to its left !

            }
            else{
                (*(*(arr + (*(location2 + m)).row) + (*(location2 + m)).column)) = (*(location2 + m)).marker + 1;
                //printf("%d\n", (*(*(arr + (*(location + m)).row) + (*(location + m)).column)));
            }
        }
    }
    // *(*arr) = 0;
    return;
}


//unused uppercase function; now inside search puzzle
// char* upcase(char* str) { 
//     char* p;
//     char* result;
//     result = (char*) malloc( strlen(str)+1 ); 
//     strcpy( result , str );
//     for( p=result; *p!='\0'; p++ ) {
//     /* Fill-in ‘A’ = 65, ‘a’ = 97, ‘Z’ = 90 , ‘z’ = 122 */
//     if (*p >= 'a' && *p <= 'z')
//     *p += -32; 
//     }
//     return result;
// }

void printPuzzleInt(int** arr){
    // This function will print out the complete puzzle grid but ints

    for(int i = 0; i < bSize; i++) {
        for(int j = 0; j < bSize; j++) {

            printf("%d", *(*(arr + i)+j));
            int x = *(*(arr + i)+j);
            int count = 1;
            while(x >= 10){ // see how long the int we are gonna print is and make sure it lines up 
                x = x / 10;
                count++;
            }
            for (int k = 0; k < 8-count; k++){
                printf(" ");
            }

        }
        printf("\n");
    }
}


void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.

    // struct letterLocation *letterLocations = (struct letterLocation*)malloc(bSize * sizeof(struct letterLocation));

    // int index1 = 0;

    int **answer = (int**)malloc(bSize * sizeof(int*)); // answer matrix <- of ints instead of chars
    for (int p = 0; p  < bSize; p++){ // make space
        *(answer + p) = (int*) malloc(bSize * sizeof(int));
    }

    char* p;
    char* new; // this new word is the uppercase version of word
    new = (char*) malloc( strlen(word)+1 ); 
    strcpy( new , word );
    for( p=new; *p!='\0'; p++ ) {
    /* Fill-in ‘A’ = 65, ‘a’ = 97, ‘Z’ = 90 , ‘z’ = 122 */
        if (*p >= 'a' && *p <= 'z')
            *p += -32; 
    }

    int wordLength = strlen(new);

    struct letterLocation *letterLocations = (struct letterLocation*)malloc(wordLength * sizeof(struct letterLocation));
    struct letterLocation *letterLocations2 = (struct letterLocation*)malloc(wordLength * sizeof(struct letterLocation));

    for (int i = 0; i < bSize; i++) {
        if (done != 0){
                //break;
        }
        for (int j = 0; j < bSize; j++) { // go thru grid
            if (done == 0){
                if (*(*(arr + i) + j) == *new) { // if match the first character of the word
                    // put location in struct !
                    (*(letterLocations)).row = i;


                    (*(letterLocations)).column = j;

                    (*(letterLocations)).marker = 0;

                    index1++; // next letter !
                    //printf("%s  %c %d %d \n", new, *new, i, j);
                    done = searchAround(arr, new, letterLocations, i, j, bSize, wordLength);
                    index1 = 0;

                    if (done != 0){
                        done2 = 1;
                    //     puzzleMap(answer, letterLocations, wordLength); // rewrite grid using locations
                    //     printf("Word found!\n");
                    //     printf("Printing the search path:\n");
                    //     printPuzzleInt(answer);
                    }
                }

            }
            else if (done2 == 1){
                if (*(*(arr + i) + j) == *new) { // if match the first character of the word
                    // put location in struct !
                    (*(letterLocations2)).row = i;


                    (*(letterLocations2)).column = j;

                    (*(letterLocations2)).marker = 0;

                    index1++; // next letter !
                    //printf("%s  %c %d %d \n", new, *new, i, j);
                    done2 = searchAround(arr, new, letterLocations2, i, j, bSize, wordLength) + 1;
                    index1 = 0;
                    //done2 = 0;
                }                
            }
        }
    }

    //searchAround(arr, new, letterLocations, 0, 0, index1, bSize, wordLength); // start at location (0,0), (m,n) later

    if(done == 0){
        printf("\nWord not found!\n");
    }
    else{
        puzzleMap(answer, letterLocations, letterLocations2, wordLength); // rewrite grid using locations
        printf("\nWord found!\n");
        printf("Printing the search path:\n");
        printPuzzleInt(answer);
    }

    return;
}