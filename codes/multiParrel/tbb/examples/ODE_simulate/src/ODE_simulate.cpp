//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <stdio.h>
#include <vector>
#include "tbb/task_scheduler_init.h"
#include "tbb/task.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"

#if defined(__linux__) || defined(__APPLE__) 
// Linux and OS X do not have _stricmp
#include <string.h>
#define _stricmp(x,y) strcasecmp(x,y)
#endif

typedef int object_t;
typedef std::vector<object_t*> world_t;
typedef std::vector<object_t*> island_t;
typedef std::vector<island_t*> islands_vector;

const unsigned int N  = 20000; // Weight of the computation complexity

const int grain_size  = 5; // Grainsize for parallel_for: hard to 
                           // find a good number if the
                           // environment changes dynamically

const int step_time   = 1; // Time to spend processing one object
                           // in dInternalStepIslandFast (solver)

const int search_time = 1; // Time to spend processing one object
                           // in processIslandsFast (islands finder)

void busy (int weight)
{
    for (int i = 0; i < weight; i++) {
        static volatile int x;
        for (int j = 0; j < N; j++)
            ++x;
    }
}

// Simulates solver 
void dInternalStepIslandFast (int obj_num, island_t& island)
{
    for (int i = 0; i < obj_num; i++)
        busy (step_time);
}

// Finds islands of connected objects and calls solver
void processIslandsFast (int counter, world_t& world)
{
    int obj_num = counter;
    for (size_t i = 0; i < world.size(); i++) {
        busy (search_time);
        if (i % counter == 0) {
            // Call solver for the found island
            dInternalStepIslandFast (obj_num, world);
        }
    }
}

// Body functor for parallel_for version
class process_islands
{
    islands_vector &p;
    int obj_num;
public:
    process_islands (islands_vector& params, int num):
                     p (params), obj_num (num) {}
    void operator() (tbb::blocked_range<int> &r) const
    {
        // Call solver for each island from the sub-range
        for (int i = r.begin(); i != r.end(); i++)
            dInternalStepIslandFast (obj_num, *p[i]);
    }
};

// Modified processIslandsFast: calls tbb::parallel_for 
// for the array of islands
void processIslandsFastPfor (int counter, world_t& world)
{
    int obj_num     = counter;
    int num_islands = 0;

    for (size_t i = 0; i < world.size(); i++) {
        busy (search_time);
        if (i % counter == 0) {
            // Just register a new island
            num_islands++;
        }
    }
    islands_vector islands(num_islands);
    // Call parallel_for for all found islands
    tbb::parallel_for (tbb::blocked_range<int>(0, num_islands,
                                               grain_size), 
                       process_islands (islands, obj_num));
}

// Task: calls solver for the given island
class process_one_island: public tbb::task
{
    island_t &p;
    int obj_num;
public:
    process_one_island (island_t& params, int num): 
                        p (params), obj_num (num) {}
    task* execute ()
    {
        dInternalStepIslandFast (obj_num, p);
        return NULL;
    }
};

void processIslandsFastTask (tbb::task& tbb_root, 
                             int counter, world_t& world);
// Root task: calls processIslandsFastTask to search for islands
// spawns process_one_island tasks for the found islands
class process_world: public tbb::task
{
    int counter;
    world_t& world;
public:
    process_world (int num, world_t& w) :
                   world (w), counter(num) {}
    task* execute ()
    {
        processIslandsFastTask (*this, counter, world);
        return NULL;
    }
};

// Modified processIslandsFast: spawns process_one_island task 
// for the island new parameter "tbb_root" is added
void processIslandsFastTask (tbb::task& tbb_root, 
                             int counter, world_t& world)
{
    int obj_num = counter;

    for (size_t i = 0; i < world.size(); i++) {
        busy (search_time);
        if (i % counter == 0) {
            // Changed from the book to avoid taking a reference
            // to a temporary (allows compile on GCC)
            island_t island;
            // Spawn the solver task immediately, 
            // not wait until all islands are found
            tbb::task& t = 
              *new (tbb_root.allocate_additional_child_of (tbb_root))
                 process_one_island (island, obj_num);
            tbb_root.spawn (t);
        }
    }
    // Join all the children tasks
    tbb_root.wait_for_all ();
}

int main (int argc, char **argv)
{
    unsigned int world_size  = 400;
    int tbb_num_threads = tbb::task_scheduler_init::automatic;

    // Process program input arguments
    unsigned int num = 0;
    for (int i=1; i<argc; i++) 
    {
        if (_stricmp(argv[i],"-numThreads")==0) {
            if ((i < argc-1) && ((num = atoi(argv[i+1])) > 0))
                tbb_num_threads = num;
        }
        else if (_stricmp(argv[i],"-numObjects")==0) {
            if ((i < argc-1) && ((num = atoi(argv[i+1])) > 1))
                world_size = num;
        }
    }

    // Initialize the world with objects
    world_t world(world_size);

    if (tbb_num_threads != tbb::task_scheduler_init::automatic)
        printf ("Number of threads: %d\n", tbb_num_threads);
    else
        printf ("Running default number of threads\n");

    printf ("Number of objects in the scene: %d\n", world_size);

    //**** Serial version:
    tbb::tick_count t1_serial = tbb::tick_count::now();

    // Frame loop: simulates dynamically changing environment:
    // total number of objects is constant, number of islands varies
    for (unsigned int i = 1; i <= world_size/2; ++i)
        processIslandsFast (i, world);

    tbb::tick_count t2_serial = tbb::tick_count::now();
    printf ("Serial time: %g seconds\n",
            (t2_serial-t1_serial).seconds ());

    //**** tbb::parallel_for version
    tbb::task_scheduler_init tbb_init(tbb_num_threads);
    tbb::tick_count t1_pfor = tbb::tick_count::now();

    // Frame loop:
    for (unsigned int i = 1; i <= world_size/2; ++i)
        processIslandsFastPfor (i, world);

    tbb::tick_count t2_pfor = tbb::tick_count::now();
    printf ("parallel_for version time: %g seconds\n", 
                  (t2_pfor-t1_pfor).seconds ());

    //**** tbb::task version:
    tbb::tick_count t1_task = tbb::tick_count::now();

    // Frame loop:
    for (unsigned int i = 1; i <= world_size/2; ++i)
    {
        tbb::task& root = 
              *new (tbb::task::allocate_root()) 
                 process_world (i, world);
        root.set_ref_count (1);
        tbb::task::spawn_root_and_wait (root);
    }

    tbb::tick_count t2_task = tbb::tick_count::now();
    printf ("Task version time: %g seconds\n", 
                  (t2_task-t1_task).seconds ());

    return 0;
}
