#include <stdlib.h>
typedef unsigned int size_t;

void * operator new(size_t size);
void operator delete(void * ptr);