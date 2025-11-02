# lab7-vectormem
# Vector Calculator V2
## This program allows the user to perform math operations on vectors, using dynamic memory to store them.

### To build:
make clean
make

### To run:
./minimat

### Supported commands:
add
subtract
multiply a vector by a number
display answer or save answer into a new vector
list
help
display a vector
clear saved vectors
quit

### Use of dynamic memory
My program uses realloc to allocate memory for a constantly changing amount of vectors.
Every time a new vector is added, the program reallocates the space needed to contain all
of the existing vectors in addition to the new one.

