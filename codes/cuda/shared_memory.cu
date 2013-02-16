/*
example is to show how to use shared memory and every block has seperate
entity for shared memory. no impact on other block's shared memory.

and we can't use memcpy to set init value for shared memory since its addr
space not in global linear. 

but how to init it, not clear now.
*/
#include <iostream>
using namespace std;

static void HandleError( cudaError_t err,const char *file, int line ) {
    if (err != cudaSuccess) {
        cout <<  cudaGetErrorString(err) << file << line << endl;
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define DIM 16
__shared__ int share[256];

__global__ void fun(int * in, int * out)
{
	
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	if (tid < DIM)
	share[0] = tid;
    //from output we can see every block has its own entity for shared memory
	out[tid] = share[0];
}

int main()
{
int * inGlobe;
int * outGlobe;
int tmp[DIM*DIM];
int tmp2[DIM][DIM];

HANDLE_ERROR(cudaMalloc((void**)&inGlobe, DIM * DIM * sizeof (int)));
HANDLE_ERROR(cudaMalloc((void**)&outGlobe,DIM * DIM * sizeof (int)));
	
for (int i = 0; i < DIM*DIM; ++i)
{
	tmp[i] = i;		
	
}

HANDLE_ERROR(cudaMemcpy( inGlobe, tmp, DIM * DIM * sizeof (int), cudaMemcpyHostToDevice ));    

fun<<<DIM,DIM>>>(inGlobe,outGlobe);
	
HANDLE_ERROR(cudaMemcpy( tmp2, outGlobe, DIM * DIM * sizeof (int), cudaMemcpyDeviceToHost ));

for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
		cout << tmp2[i][j] << "  " ;
	cout << endl;
}
 int k;
 cin >> k;
return 0;
}

