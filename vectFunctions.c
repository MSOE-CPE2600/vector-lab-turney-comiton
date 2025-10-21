#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vector.h"
#include "vectFunctions.h"

// Define global array and count
int vectCount = 1;
struct vector vectArray[vectCount];
struct vector *pointers[vectCount];


// Check if string is an operator
int isOperator(const char *s) {
    return strcmp(s, "+") == 0 ||
           strcmp(s, "-") == 0 ||
           strcmp(s, "*") == 0 ||
           strcmp(s, "=") == 0;
}

// Find vector by name
struct vector* getVector(const char *name) {
    for (int i = 0; i < vectCount; i++) {
        if (strcmp(vectArray[i].name, name) == 0) {
            return &vectArray[i];
        }
    }
    return NULL;
}

// Add or update a vector
void newVector(const char *X, const char *Y, const char *Z, const char *name) {
    
    double x = strtod(X, NULL);
    double y = strtod(Y, NULL);
    double z = strtod(Z, NULL);

    // Update existing vector
    struct vector *v = getVector(name);
    if (v) {
        v->x = x;
        v->y = y;
        v->z = z;
        printf("Updated vector %s = [%.2f %.2f %.2f]\n", name, x, y, z);
        return;
    }

    // Add new vector
    
    strcpy(vectArray[vectCount].name, name);
    vectArray[vectCount].x = x;
    vectArray[vectCount].y = y;
    vectArray[vectCount].z = z;
    vectCount++;
    printf("Added vector %s = [%.2f %.2f %.2f]\n", name, x, y, z);
    
}

// Vector operations

// add
void add(const char *v1Name, const char *v2Name, const char *destName) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);
    
    struct vector *v2 = malloc(sizeof(struct vector));
    *v2 = getVector(v2Name);
    
    if (!v1 || !v2) {
        printf("Error: missing operand.\n");
        return;
    }

    if (!getVector(destName)) {
        newVector("0", "0", "0", destName);
    }

    struct vector *dest = malloc(sizeof(struct vector));
    *dest = getVector(destName);
    dest->x = v1->x + v2->x;
    dest->y = v1->y + v2->y;
    dest->z = v1->z + v2->z;

    printf("%s = [%.2f %.2f %.2f]\n", destName, dest->x, dest->y, dest->z);
}
// add but just display; not into a new vector
void addDisplay(const char *v1Name, const char *v2Name) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);
    
    struct vector *v2 = malloc(sizeof(struct vector));
    *v2 = getVector(v2Name);

    if (!v1 || !v2) {
        printf("Error: missing operand.\n");
        return;
    }

    double x = v1->x + v2->x;
    double y = v1->y + v2->y;
    double z = v1->z + v2->z;

    printf("ans = [%.2f %.2f %.2f]\n", x, y, z);
}
// subtract
void subtract(const char *v1Name, const char *v2Name, const char *destName) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);
    
    struct vector *v2 = malloc(sizeof(struct vector));
    *v2 = getVector(v2Name);

    if (!v1 || !v2) {
        printf("Error: missing operand.\n");
        return;
    }

    if (!getVector(destName)) {
        newVector("0", "0", "0", destName);
    }
    struct vector *dest = malloc(sizeof(struct vector));
    *dest = getVector(destName);
    dest->x = v1->x - v2->x;
    dest->y = v1->y - v2->y;
    dest->z = v1->z - v2->z;

    printf("%s = [%.2f %.2f %.2f]\n", destName, dest->x, dest->y, dest->z);
}
// subtract but just display; not into a new vector
void subtractDisplay(const char *v1Name, const char *v2Name) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);
    
    struct vector *v2 = malloc(sizeof(struct vector));
    *v2 = getVector(v2Name);

    if (!v1 || !v2) {
        printf("Error: missing operand.\n");
        return;
    }

    double x = v1->x - v2->x;
    double y = v1->y - v2->y;
    double z = v1->z - v2->z;

    printf("ans = [%.2f %.2f %.2f]\n", x, y, z);
}
// multiply
void multiply(const char *v1Name, const char *b, const char *destName) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);

    if (!v1) {
        printf("Error: missing operand.\n");
        return;
    }

    double B = strtod(b, NULL);

    if (!getVector(destName)) {
        newVector("0", "0", "0", destName);
    }

    struct vector *dest = malloc(sizeof(struct vector));
    *dest = getVector(destName);
    dest->x = v1->x * B;
    dest->y = v1->y * B;
    dest->z = v1->z * B;

    printf("%s = [%.2f %.2f %.2f]\n", destName, dest->x, dest->y, dest->z);
}
// multiply but just display; not into a new vector
void multiplyDisplay(const char *v1Name, const char *b) {
    struct vector *v1 = malloc(sizeof(struct vector));
    *v1 = getVector(v1Name);

    if (!v1) {
        printf("Error: missing operand.\n");
        return;
    }
    double B = strtod(b, NULL);

    double x = v1->x * B;
    double y = v1->y * B;
    double z = v1->z * B;

    printf("ans = [%.2f %.2f %.2f]\n", x, y, z);
}
// display a chosen vector
void showVector(const char *name){
    struct vector *v = malloc(sizeof(struct vector));
    *v = getVector(name);
    if (!v) {
        printf("Error: vector not found.\n");
        return;
    }
    printf("%s = [%.2f %.2f %.2f]\n", name, v->x, v->y, v->z);
}
