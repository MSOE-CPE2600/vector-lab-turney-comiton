/*
 * Filename: main.c
 * Author: Nicholas Comito
 * Date: 10/24/2025
 * Description: Driver for dynamic minimatlab
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"
#include "vectFunctions.h"

int main(int argc, char *argv[]) {
    printf("Welcome to vector calculator\n");

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("This program allows you to initialize vectors, view them, perform\n");
        printf("operations on them such as addition, subtraction, and scalar multiplication.\n");
        printf("Type:    a = x y z    to initialize a vector,\n");
        printf("c = b + a     to do an operation, for example.\n");
        printf("Commands: help, list, clear, load <fname>, save <fname>, quit\n");
    }

    char input[256];
    int quit = 0;

    while (!quit) {
        printf("minimat> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        // trim trailing newline
        input[strcspn(input, "\r\n")] = 0;

        // skip leading spaces
        char *line = input;
        while (*line && isspace((unsigned char)*line)) line++;
        if (*line == 0) continue;

        if (strcmp(line, "help") == 0) {
            printf("Commands: help, list, clear, load <fname>, save <fname>, quit\n");
            continue;
        }
        if (strcmp(line, "quit") == 0){ 
            quit = 1;
            continue;
        }
        if (strcmp(line, "list") == 0) {
            if (vectCount == 0) printf("No vectors stored\n");
            else for (int i=0;i<vectCount;i++)
                printf("%s = [%.2f %.2f %.2f]\n", vectArray[i].name,
                       vectArray[i].x, vectArray[i].y, vectArray[i].z);
            continue;
        }
        if (strcmp(line, "clear") == 0) {
            clearVectors(); printf("All vectors removed\n");
            continue;
        }

        if (strncmp(line, "load ", 5) == 0) {
            char *fname = line+5; while (*fname && isspace((unsigned char)*fname)) fname++;
            if (*fname == 0) { printf("Usage: load <filename>\n"); continue; }
            if (loadFromFile(fname) == 0) printf("Loaded %s\n", fname);
            continue;
        }
        if (strncmp(line, "save ", 5) == 0) {
            char *fname = line+5;
            while (*fname && isspace((unsigned char)*fname)) fname++;
            if (*fname == 0) { printf("Usage: save <filename>\n"); continue; }
            if (saveToFile(fname) == 0) printf("Saved to %s\n", fname);
            continue;
        }

        // tokenize input
        char copy[256];
        strncpy(copy, line, sizeof(copy)-1);
        copy[sizeof(copy)-1] = 0;
        char *A = strtok(copy," ");
        char *B = strtok(NULL," ");
        char *C = strtok(NULL," ");
        char *D = strtok(NULL," ");
        char *E = strtok(NULL," ");

        if (!A) continue;
        if (!B && !C && !D && !E) { showVector(A); continue; }

        if (B && strcmp(B,"=")==0) {
            if (C && D && E && !isOperator(C) && !isOperator(D) && !isOperator(E)) {
                newVector(C,D,E,A);
            } else if (C && D && E && isOperator(D)) {
                if (strcmp(D,"+")==0) add(C,E,A);
                else if (strcmp(D,"-")==0) subtract(C,E,A);
                else if (strcmp(D,"*")==0) multiply(C,E,A);
                else printf("Invalid operator.\n");
            } else { printf("Invalid input.\n"); }
            continue;
        }

        if (B && C && !D && !E) {
            if (strcmp(B,"+")==0) addDisplay(A,C);
            else if (strcmp(B,"-")==0) subtractDisplay(A,C);
            else if (strcmp(B,"*")==0) multiplyDisplay(A,C);
            else printf("Invalid input.\n");
            continue;
        }

        printf("Invalid input.\n");
    }

    printf("Goodbye!\n");
    return 0;
}