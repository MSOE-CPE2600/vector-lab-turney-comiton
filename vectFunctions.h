
#ifndef VECTARRAY_H
#define VECTARRAY_H

#include "vector.h"
extern int vectCount;
extern struct vector vectArray[vectCount];

int isOperator(const char *s);
struct vector* getVector(const char *name);
void newVector(const char *X, const char *Y, const char *Z, const char *name);
void add(const char *v1Name, const char *v2Name, const char *destName);
void addDisplay(const char *v1Name, const char *v2Name);
void subtract(const char *v1Name, const char *v2Name, const char *destName);
void subtractDisplay(const char *v1Name, const char *v2Name);
void multiply(const char *v1Name, const char *b, const char *destName);
void multiplyDisplay(const char *v1Name, const char *v2Name);
void showVector(const char *name);
#endif