#ifndef VECT_FUNCTIONS_H
#define VECT_FUNCTIONS_H

#include "vector.h"

int loadFromFile(const char *filename);
int saveToFile(const char *filename);
void clearVectors(void);

void showVector(const char *name);
int isOperator(const char *s);
void newVector(const char *x, const char *y, const char *z, const char *name);
void add(const char *v1, const char *v2, const char *result);
void subtract(const char *v1, const char *v2, const char *result);
void multiply(const char *v1, const char *v2, const char *result);
void addDisplay(const char *v1, const char *v2);
void subtractDisplay(const char *v1, const char *v2);
void multiplyDisplay(const char *v1, const char *v2);

#endif