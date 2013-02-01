/*
g++ -O2 -DNDEBUG m_scalable.cc -ltbb -lrt -ltbbmalloc 
*/

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


//following for c++
/*
void* operator new (size_t size) throw (std::bad_alloc)
{
    if (size == 0) size = 1; 
    if (void* ptr = scalable_malloc (size))
        return ptr;
    throw std::bad_alloc ();
}

void* operator new[] (size_t size) throw (std::bad_alloc)
{
    return operator new (size);
}

void* operator new (size_t size, const std::nothrow_t&) throw ()
{
    if (size == 0) size = 1; 
    if (void* ptr = scalable_malloc (size))
        return ptr;
    return NULL;
}

void* operator new[] (size_t size, const std::nothrow_t&) throw ()
{
    return operator new (size, std::nothrow);
}

void operator delete (void* ptr) throw ()
{
    if (ptr != 0) scalable_free (ptr);
}

void operator delete[] (void* ptr) throw ()
{
    operator delete (ptr);
}

void operator delete (void* ptr, const std::nothrow_t&) throw ()
{
    if (ptr != 0) scalable_free (ptr);
}

void operator delete[] (void* ptr, const std::nothrow_t&) throw ()
{
    operator delete (ptr, std::nothrow);
}

class do_for {
    const size_t chunk;
public:
    do_for (size_t _chunk): chunk (_chunk) {}
    void operator() (tbb::blocked_range<int> &r) const {
        for (int i = r.begin(); i != r.end(); ++i) {
            // scalable_malloc will be called to allocate the memory
            // for this array of int's
            int *p = new int [chunk];
            // scalable_free will be called to deallocate the memory
            // for this array of int's
            delete[] p;
        }

    }
};

int main (int argc, char** argv)
{
    const size_t size = 1000;
    const size_t chunk = 10;
    const size_t grain_size = 200;
    // Initialize TBB
    tbb::task_scheduler_init tbb_init;
    // scalable_malloc will be called to allocate the memory
    //  for this array of int's
    int *p = new int[size];

    tbb::parallel_for (tbb::blocked_range<int> (0, size, grain_size),
                       do_for (chunk));

    return 0;
}
*/
