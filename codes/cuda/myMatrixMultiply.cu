/*
sample to show the matrix multiply. it is for square.
need a little bit modification for rectangle.
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

const int DIM = 4;
const int block_size = 4;

__global__ void multi(int * A, int * B, int * C)
{
   __shared__ int As[block_size][block_size];       
   __shared__ int Bs[block_size][block_size];

	// Block index
    int bx = blockIdx.x;
    int by = blockIdx.y;

    // Thread index
    int tx = threadIdx.x;
    int ty = threadIdx.y;

	int len = DIM * block_size;

    // Index of the first sub-matrix of A processed by the block
    int aBegin = len * by;

    // Index of the last sub-matrix of A processed by the block
    int aEnd   = aBegin + len - 1;

    // Step size used to iterate through the sub-matrices of A
    int aStep  = block_size;

    // Index of the first sub-matrix of B processed by the block
    int bBegin = block_size * bx;

    // Step size used to iterate through the sub-matrices of B
    int bStep  = block_size * len;

    // Csub is used to store the element of the block sub-matrix
    // that is computed by the thread
    float Csub = 0;

    // Loop over all the sub-matrices of A and B
    // required to compute the block sub-matrix
    for (int a = aBegin, b = bBegin;
             a <= aEnd;
             a += aStep, b += bStep) 
	{        
        As[ty][tx] = A[a + len * ty + tx];
        Bs[ty][tx] = B[b + len * ty + tx];       
        __syncthreads();       

        for (int k = 0; k < block_size; ++k)
            Csub += As[ty][k] * Bs[k][tx];
		__syncthreads();
    }
   
    int c = len * (by * block_size + ty) + block_size * bx + tx;
    C[c] = Csub;	
}

int main()
{
int * inGlobe;
int * in2Globe;
int * outGlobe;

HANDLE_ERROR(cudaMalloc((void**)&inGlobe,DIM * DIM * block_size * block_size * sizeof(int)));
HANDLE_ERROR(cudaMalloc((void**)&in2Globe,DIM * DIM * block_size * block_size * sizeof(int)));
HANDLE_ERROR(cudaMalloc((void**)&outGlobe,DIM * DIM * block_size * block_size * sizeof(int)));


int tmp[DIM*DIM* block_size * block_size];
for(int i=0;i<DIM*DIM;++i)
	for(int j=0;j<block_size * block_size;++j)
	tmp[i*DIM*DIM + j] = 2;

HANDLE_ERROR(cudaMemcpy(inGlobe,tmp,DIM*DIM* block_size * block_size*sizeof(int),cudaMemcpyHostToDevice));
for(int i=0;i<DIM*DIM;++i)
	for(int j=0;j<block_size * block_size;++j)
	tmp[i*DIM*DIM + j] = 5;

HANDLE_ERROR(cudaMemcpy(in2Globe,tmp,DIM*DIM* block_size * block_size*sizeof(int),cudaMemcpyHostToDevice));

for(int i=0;i<DIM*DIM;++i)
	for(int j=0;j<block_size * block_size;++j)
	tmp[i*DIM*DIM + j] = 0;

HANDLE_ERROR(cudaMemcpy(outGlobe,tmp,DIM*DIM* block_size * block_size*sizeof(int),cudaMemcpyHostToDevice));

dim3 bdim(DIM,DIM);
dim3 tdim(block_size,block_size);

multi<<<bdim,tdim>>>(inGlobe,in2Globe,outGlobe);
HANDLE_ERROR(cudaMemcpy(tmp,outGlobe,DIM*DIM* block_size * block_size*sizeof(int),cudaMemcpyDeviceToHost));
cudaDeviceSynchronize();

for(int i=0;i<DIM*DIM;++i)
{
	for(int j=0;j<block_size * block_size;++j)	
	   cout << " " << tmp[i*DIM*DIM + j];
	cout << endl;
}


 int k;
 cin >> k;
return 0;
}

