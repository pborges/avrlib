#ifndef __AVR_BOOTSTRAP__
#define __AVR_BOOTSTRAP__

#include <stdlib.h>
#include "../io/digitalio.h"

typedef unsigned int size_t;

void * operator new(size_t size);
void operator delete(void * ptr);

#endif