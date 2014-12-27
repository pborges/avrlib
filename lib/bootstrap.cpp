#include "bootstrap.h"

void * operator new(size_t size) {
	return malloc(size);
}
void operator delete(void * ptr);