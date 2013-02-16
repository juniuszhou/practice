/*
example to show how to use stream and async method to make the data
transfer and kernel function executed concurrently.
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
	*out = *in + 1000*tid;
}

int main()
{
int * inGlobe;
int * outGlobe;
int tmp[DIM*DIM];
int tmp2[DIM*DIM];

cudaStream_t    stream;
HANDLE_ERROR( cudaStreamCreate( &stream ) );

HANDLE_ERROR(cudaMalloc((void**)&inGlobe, DIM * DIM * sizeof (int)));
HANDLE_ERROR(cudaMalloc((void**)&outGlobe, DIM * DIM * sizeof (int)));
	
for (int i = 0; i < DIM*DIM; ++i)
	tmp[i] = i;	

for (int i = 0; i < DIM*DIM; ++i)
{
cudaMemcpyAsync(inGlobe+i,tmp+i,sizeof(int),cudaMemcpyHostToDevice,stream ) ;
//0 is device and stream is exec stream.
fun<<<1,1,0,stream>>>(inGlobe+i,outGlobe+i);
cudaMemcpyAsync(tmp2+i,outGlobe+i,sizeof(int),cudaMemcpyDeviceToHost,stream);
}

 HANDLE_ERROR( cudaStreamSynchronize( stream ) );

for (int i = 0; i < DIM * DIM; ++i)	
		cout << tmp2[i] << "  " ;
	

 int k;
 cin >> k;
return 0;
}

