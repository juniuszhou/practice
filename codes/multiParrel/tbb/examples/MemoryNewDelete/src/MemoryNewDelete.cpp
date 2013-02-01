//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/scalable_allocator.h"

// No retry loop because we assume that scalable_malloc does
// all it takes to allocate the memory, so calling it repeatedly
// will not improve the situation at all
//
// No use of std::new_handler because it cannot be done in portable
// and thread-safe way (see sidebar)
//
// We throw std::bad_alloc() when scalable_malloc returns NULL
//(we return NULL if it is a no-throw implementation)

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
