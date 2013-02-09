/*
texture<DataType,Type,ReadMode>

Type:
cudaTextureType1D
cudaTextureType2D
cudaTextureType3D
cudaTextureType1DLayered
cudaTextureType2DLayered

ReadMode:
cudaReadModeElementType
cudaReadModeNormalizedFloat

*/


#include <iostream>
#include "stdio.h"
using namespace std;
const int DIM = 16;
texture<float,2,cudaReadModeElementType>  texIn;

__global__ void fun(float * in, float * out)
{
	int x = threadIdx.x;
	int y = threadIdx.y;	
	int tid = threadIdx.x + threadIdx.y * blockDim.x;
	out[tid] = tex2D(texIn,fx,fy) + 0.1;
	
}

int main()
{
float * inGlobe;
float * outGlobe;
float tmp1[DIM][DIM];
float tmp[DIM][DIM];
dim3    threads(DIM,DIM);

texIn.normalized = true;                      // access with normalized texture coordinates
    texIn.filterMode = cudaFilterModeLinear;      // linear interpolation

cudaMalloc((void**)&inGlobe,DIM * DIM );
cudaMalloc((void**)&outGlobe,DIM * DIM * 4);
cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
cudaBindTexture2D( NULL, texIn,inGlobe,
                 desc, DIM, DIM,
                 DIM * sizeof (float) );
	
for (int i = 0; i < DIM; ++i)
	for (int j = 0; j < DIM; ++j)
		tmp1[i][j] = (i*DIM + j + 0.1) / 256;

cudaMemcpy( inGlobe, tmp1, DIM * DIM * sizeof (float), cudaMemcpyHostToDevice );    

fun<<<1,threads>>>(inGlobe,outGlobe);
	
cudaMemcpy(tmp,outGlobe,  DIM * DIM * sizeof (float), cudaMemcpyDeviceToHost );

for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
		printf("%f ", tmp[i][j]);
	cout << endl;
}
 int k;
 cin >> k;
return 0;
}

