/*
 * Filename: vectFunctions.c
 * Author: Nicholas Comito
 * Date: 10/24/2025
 * Description: functions for dynamic minimatlab
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vectFunctions.h"

struct vector *vectArray = NULL;
int vectCount = 0;
static int vectCapacity = 0;

// helper
static void ensureCapacity(void) {
    if (vectCount >= vectCapacity) {
        vectCapacity = (vectCapacity == 0) ? 4 : vectCapacity * 2;
        struct vector *newArr = realloc(vectArray, vectCapacity * sizeof(struct vector));
        if (!newArr) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        vectArray = newArr;
    }
}

static struct vector *findVector(const char *name) {
    for (int i = 0; i < vectCount; i++) {
        if (vectArray[i].name[0] == name[0]) return &vectArray[i];
    }
    return NULL;
}

// initialize vector
void newVector(const char *x, const char *y, const char *z, const char *name) {
    struct vector *existing = findVector(name);
    if (existing) {
        existing->x = atof(x);
        existing->y = atof(y);
        existing->z = atof(z);
        printf("Vector %s updated.\n", name);
        return;
    }

    ensureCapacity();
    vectArray[vectCount].name[0] = name[0];
    vectArray[vectCount].name[1] = '\0';
    vectArray[vectCount].x = atof(x);
    vectArray[vectCount].y = atof(y);
    vectArray[vectCount].z = atof(z);
    vectCount++;
    printf("Vector %s added.\n", name);
}

void showVector(const char *name) {
    struct vector *v = findVector(name);
    if (!v) {
        printf("Vector %s not found.\n", name);
        return;
    }
    printf("%s = [%.2f %.2f %.2f]\n", v->name, v->x, v->y, v->z);
}

int isOperator(const char *s) {
    return (strcmp(s, "+") == 0 || strcmp(s, "-") == 0 || strcmp(s, "*") == 0);
}

// operations
void add(const char *v1, const char *v2, const char *result) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) {
        printf("Error: vector not found.\n"); 
        return;
    }
    char sx[32], sy[32], sz[32];
    snprintf(sx, sizeof(sx), "%f", a->x + b->x);
    snprintf(sy, sizeof(sy), "%f", a->y + b->y);
    snprintf(sz, sizeof(sz), "%f", a->z + b->z);
    newVector(sx, sy, sz, result);
}

void subtract(const char *v1, const char *v2, const char *result) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) { 
        printf("Error: vector not found.\n"); 
        return; 
    }
    char sx[32], sy[32], sz[32];
    snprintf(sx, sizeof(sx), "%f", a->x - b->x);
    snprintf(sy, sizeof(sy), "%f", a->y - b->y);
    snprintf(sz, sizeof(sz), "%f", a->z - b->z);
    newVector(sx, sy, sz, result);
}

void multiply(const char *v1, const char *v2, const char *result) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) { 
        printf("Error: vector not found.\n"); 
        return; 
    }
    double dot = a->x*b->x + a->y*b->y + a->z*b->z;
    char sx[32];
    snprintf(sx, sizeof(sx), "%f", dot);
    newVector(sx, "0", "0", result);
}

// Display-only
void addDisplay(const char *v1, const char *v2) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) { 
        printf("Error: vector not found.\n"); 
        return; 
    }
    printf("[%s + %s] = [%.2f %.2f %.2f]\n", v1, v2, a->x+b->x, a->y+b->y, a->z+b->z);
}

void subtractDisplay(const char *v1, const char *v2) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) { 
        printf("Error: vector not found.\n"); 
        return; 
    }
    printf("[%s - %s] = [%.2f %.2f %.2f]\n", v1, v2, a->x-b->x, a->y-b->y, a->z-b->z);
}

void multiplyDisplay(const char *v1, const char *v2) {
    struct vector *a = findVector(v1);
    struct vector *b = findVector(v2);
    if (!a || !b) { 
        printf("Error: vector not found.\n"); 
        return; 
    }
    printf("[%s ⋅ %s] = %.2f\n", v1, v2, a->x*b->x + a->y*b->y + a->z*b->z);
}

// memory
void clearVectors(void) {
    free(vectArray);
    vectArray = NULL;
    vectCount = 0;
    vectCapacity = 0;
}

// file I/O
int loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Error opening file"); 
        return -1; 
    }

    clearVectors();

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Remove trailing \r\n or \n
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        char name[2], sx[32], sy[32], sz[32];
        if (sscanf(line, "%1[^,],%31[^,],%31[^,],%31[^,]", name, sx, sy, sz) == 4) {
            newVector(sx, sy, sz, name);
        } else {
            printf("Skipping malformed line: %s\n", line);
        }
    }

    fclose(fp);
    return 0;
}

int saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("Error opening file for write"); return -1; }

    for (int i = 0; i < vectCount; i++) {
        fprintf(fp, "%s,%.6f,%.6f,%.6f\n",
                vectArray[i].name, vectArray[i].x, vectArray[i].y, vectArray[i].z);
    }

    fclose(fp);
    return 0;
}

// Exit handler to free memory
static void freeOnExit(void) {
    clearVectors();
}

// Register exit handler automatically
__attribute__((constructor)) static void registerExitHandler(void) {
    atexit(freeOnExit);
}