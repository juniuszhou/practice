/*
example to show how to use array and texture to get value from it.
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

const int DIM = 16;

texture<int,2,cudaReadModeElementType> texArray;
__global__ void fun(int * in)
{
	int x = threadIdx.x;
	int y = blockIdx.x;
	in[x + y*blockDim.x] = tex2D(texArray,x,y) * 2;
}

int main()
{
int * inGlobe;
cudaMalloc((void**)&inGlobe,DIM*DIM*sizeof(int));
int tmp[DIM*DIM];
for(int i=0;i<DIM*DIM;++i)
	tmp[i] = i;

cudaArray * dev_array;
cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<int>();

HANDLE_ERROR(cudaMallocArray(&dev_array,&channelDesc, DIM , DIM ));
HANDLE_ERROR(cudaMemcpyToArray(dev_array,0,0,tmp,DIM*DIM*sizeof(int),cudaMemcpyHostToDevice));

HANDLE_ERROR(cudaBindTextureToArray(texArray, dev_array, channelDesc));

fun<<<DIM,DIM>>>(inGlobe);
HANDLE_ERROR(cudaMemcpy(tmp,inGlobe,DIM*DIM*sizeof(int),cudaMemcpyDeviceToHost));
cudaDeviceSynchronize();

for(int i=0;i<DIM*DIM;++i)
	cout << " " << tmp[i];
 int k;
 cin >> k;
return 0;
}



     �d35                     �A�  _rels/SD �   UT �FEPK       ! �J���   W           ��Z  _rels/.relsSD �   UT ��PK      1  �    