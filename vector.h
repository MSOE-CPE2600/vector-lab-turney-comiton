/*
 * Filename: main.c
 * Author: Nicholas Comito
 * Date: 10/24/2025
 * Description: Driver for dynamic minimatlab
 */
#ifndef VECTOR_H
#define VECTOR_H

struct vector {
    char name[2];   
    double x, y, z;
};

// Global dynamic array and count
extern struct vector *vectArray;
extern int vectCount;

#endif