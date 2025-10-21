#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vectFunctions.h"

int main(int argc, char *argv[]) {
    printf("Welcome to vector calculator\n");
    // -h flag for help
    if (argc > 1 && strcmp(argv[1], "-h") == 0){
            printf("This program allows you to initialize vectors, view them, perform \n");
            printf("operations on them such as addition, subtraction, and scalar multiplication. \n");
            printf("Simply type    a = x y z    in order to initialize a vector, or \n");
            printf("c = b + a     to do an operation, for example. Enter 'quit' to quit\n");
        
        }

    char input[100];
    int quit = 0;
        // loop until click
    while (!quit) {
        printf("minimat> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';  // remove newline

        // help
        if (strcmp(input, "help") == 0){
            printf("This program allows you to initialize vectors, view them, perform \n");
            printf("operations on them such as addition, subtraction, and scalar multiplication. \n");
            printf("Simply type    a = x y z    in order to initialize a vector, or \n");
            printf("c = b + a     to do an operation, for example. Enter 'quit' to quit\n");
            continue;
        }

        // quit command
        if (strcmp(input, "quit") == 0) {
            quit = 1;
            continue;
        }

        // list command
        if (strcmp(input, "list") == 0){
            if(vectCount == 0){
                printf("No vectors stored\n");
                continue;
            }

            for(int i = 0; i < 10; i++){
                printf("%s = [%.2f %.2f %.2f]\n", vectArray[i].name
                                                , vectArray[i].x
                                                , vectArray[i].y
                                                , vectArray[i].z);

            }
            continue;
        }

        // clear command
        if(strcmp(input, "clear") == 0){
            for(int i = 0; i < vectCount; i++){
                free()
            }
            vectCount = 0;
            printf("All vectors removed\n");

            continue;
        }

        // Tokenize input
        char *A = strtok(input, " ");
        char *B = strtok(NULL, " ");
        char *C = strtok(NULL, " ");
        char *D = strtok(NULL, " ");
        char *E = strtok(NULL, " ");

        if (!A) continue;

        // Single vector display: "a"
        if (!B && !C && !D && !E) {
            showVector(A);
            continue;
        }

        // Assignment: "A = 1 2 3" or "A = B + C" or "A = B * k"
        if (B && strcmp(B, "=") == 0) {
            if (C && D && E && !isOperator(C) && !isOperator(D) && !isOperator(E)) {
                // A = x y z
                newVector(C, D, E, A);
            } else if (C && D && E && isOperator(D)) {
                // A = B + C, A = B - C, A = B * k
                if (strcmp(D, "+") == 0) add(C, E, A);
                else if (strcmp(D, "-") == 0) subtract(C, E, A);
                else if (strcmp(D, "*") == 0) multiply(C, E, A);
                else printf("Invalid input.\n");
            } else {
                printf("Invalid input.\n");
            }
            continue;
        }

        // Operations without assignment: "A + B", "A * k", "A - B"
        if (B && C && !D && !E) {
            if (strcmp(B, "+") == 0) addDisplay(A, C);
            else if (strcmp(B, "-") == 0) subtractDisplay(A, C);
            else if (strcmp(B, "*") == 0) multiplyDisplay(A, C);
            else printf("Invalid input.\n");
            continue;
        }

        printf("Invalid input.\n");
    }

    printf("Goodbye!\n");
    return 0;
}