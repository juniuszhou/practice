/*
example to show how to use host memory in cuda func.
after allocate memory in host, cuda can operate it directly using pointer.
the result is transparent to host
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
	out[tid] = tid;
}

int main()
{
int * inGlobe;
int * outGlobe;
int tmp[DIM*DIM];
int * host_a;

HANDLE_ERROR(cudaHostAlloc( (void**)&host_a,DIM * DIM * sizeof(int),cudaHostAllocDefault ));

for (int i = 0; i < DIM*DIM; ++i)
{
	host_a[i] = i;	
} 

HANDLE_ERROR(cudaMalloc((void**)&inGlobe, DIM * DIM * sizeof (int)));
HANDLE_ERROR(cudaMalloc((void**)&outGlobe,DIM * DIM * sizeof (int)));
	
for (int i = 0; i < DIM*DIM; ++i)
{
	tmp[i] = i;	
}  

fun<<<DIM,DIM>>>(inGlobe,host_a);

for (int i = 0; i < DIM * DIM; ++i)	
		cout << host_a[i] << "  " ;
	

 int k;
 cin >> k;
return 0;
}


/*
After the host memory mapped to device, you can use cudaHostGetDevicePointer
get the addr in device. then access the data transparent.
data transfer will be implicit. cuda core can optimize for it.
cuda core automatically overlap the data transfer and kernel exec.
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
	//int  * dev_a;
	
	out[tid] = tid;
}

int main()
{
int * inGlobe;
int * outGlobe;
int tmp[DIM*DIM];
int * host_a;

HANDLE_ERROR(cudaHostAlloc( (void**)&host_a,DIM * DIM * sizeof(int),
	cudaHostAllocWriteCombined |
                              cudaHostAllocPortable |
                              cudaHostAllocMapped ));

for (int i = 0; i < DIM*DIM; ++i)
{
	host_a[i] = i;	
} 

HANDLE_ERROR(cudaMalloc((void**)&inGlobe, DIM * DIM * sizeof (int)));
HANDLE_ERROR(cudaMalloc((void**)&outGlobe,DIM * DIM * sizeof (int)));
	
for (int i = 0; i < DIM*DIM; ++i)
{
	tmp[i] = i;	
}

int * dev_out ;

HANDLE_ERROR(cudaHostGetDevicePointer( &dev_out, host_a, 0 ));

fun<<<DIM,DIM>>>(inGlobe,dev_out);

for (int i = 0; i < DIM * DIM; ++i)	
		cout << host_a[i] << "  " ;
	

 int k;
 cin >> k;
return 0;
}

