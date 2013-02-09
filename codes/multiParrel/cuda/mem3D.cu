/*
this example to show malloc 2D interface used to get a memory
optimized add padding then make sure alignment is better for fetch
*/

#include <common_functions.h>
#include <iostream>
using namespace std;

__global__ void MyKernel(cudaPitchedPtr devPitchedPtr, int width, int height, int depth) 
{ 
    char* devPtr = devPitchedPtr.ptr; 
    size_t pitch = devPitchedPtr.pitch;
    size_t slicePitch = pitch * height; 

    for (int z = 0; z < depth; ++z) 
    { 
        char* slice = devPtr + z * slicePitch; 
        for (int y = 0; y < height; ++y) 
        { 
            float* row = (float*)(slice + y * pitch); 
            for (int x = 0; x < width; ++x) 
            { 
                float element = row[x]; 
            } 
        }
    } 
}


int main(int argc, char **argv)
{
   int width = 64, height = 64, depth = 64;

   //assign a 3D access mode
    //how about if we set depth as 1
   cudaExtent extent = make_cudaExtent(width * sizeof(float), height, depth);
   
   cudaPitchedPtr devPitchedPtr;
   //get a block 3D memory
   cudaMalloc3D(&devPitchedPtr, extent);
   MyKernel<<<100, 512>>>(devPitchedPtr, width, height, depth);
   cin >> width;
   return 0;
}

