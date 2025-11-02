#ifndef VECTOR_H
#define VECTOR_H
#define MAX_VECTORS 10

struct vector {
    char name[20];
    double x;
    double y;
    double z;
};

// Declare the global array and count
extern struct vector vectArray[MAX_VECTORS];
extern int vectCount;
#endif
