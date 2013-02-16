/*
this example to show malloc 2D interface used to get a memory
optimized add padding then make sure alignment is better for fetch
*/

#include <common_functions.h>
#include <iostream>
using namespace std;

__global__ void MyKernel(char* devPtr, size_t pitch, int width, int height)
{ 
	for (int r = 0; r < height; ++r)
	{ 
		float* row = (float*)((char*)devPtr + r * pitch);
		for (int c = 0; c < width; ++c) 
		{
			float element = row[c]; 
		} 
	} 
}

int main(int argc, char **argv)
{
   int width = 64, height = 64; 
   char* devPtr; size_t pitch; 
   cudaMallocPitch(&devPtr, &pitch, width * sizeof(char), height);
   cout << sizeof(float) << endl;
   cout << pitch << endl;
   MyKernel<<<100, 512>>>(devPtr, pitch, width, height);
   cin >> width;
   return 0;
}

