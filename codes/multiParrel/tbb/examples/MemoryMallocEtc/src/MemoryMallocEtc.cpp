//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <cstdio>
#include "tbb/scalable_allocator.h"

extern "C" void * scalable_malloc(size_t size);
extern "C" void   scalable_free(void* object);
extern "C" void * scalable_realloc(void* ptr, size_t size);
extern "C" void * scalable_calloc(size_t nobj, size_t size);
#define calloc  scalable_calloc
#define malloc  scalable_malloc
#define realloc scalable_realloc
#define free    scalable_free

int main( int argc, char* argv[] ) {
	void* a = malloc(10);
	void* b = calloc(10, sizeof(int));
	printf("a:%p b:%p\n", a, b);

	a = realloc(a, 20);
	b = realloc(b, 20);
	printf("a:%p b:%p\n", a, b);

	free(a);
	free(b);
}
