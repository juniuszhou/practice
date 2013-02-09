/*
the char will map to [-1,1]

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


*/
#include <iostream>
using namespace std;

#define DIM 16
texture<char,1,cudaReadModeNormalizedFloat>  texIn;


__global__ void fun(char * in, float * out)
{

	int tid = threadIdx.x + blockIdx.x * blockDim.x;
    //we can access to texture memory like normal global memory
	//out[tid] = in[tid] * 2;
	out[tid] = tex1Dfetch(texIn,tid);
}

int main()
{
char * inGlobe;
float * outGlobe;
char tmp[DIM][DIM];
float tmp2[DIM][DIM];

cudaMalloc((void**)&inGlobe,DIM * DIM  );
cudaMalloc((void**)&outGlobe,DIM * DIM * sizeof (float));
//cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
cudaBindTexture( NULL, texIn,inGlobe,                
                 DIM * DIM * sizeof (char) );
	
for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
	{
		tmp[i][j] = i * DIM + j;
		//cout << tmp[i][j] << "  " ;
	}
	//cout << endl;
}

cudaMemcpy( inGlobe, tmp, DIM * DIM, cudaMemcpyHostToDevice );    

fun<<<DIM,DIM>>>(inGlobe,outGlobe);
	
cudaMemcpy( tmp2, outGlobe, DIM * DIM * sizeof (float), cudaMemcpyDeviceToHost );

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



/*
the unsigned char will map to [0,1]
*/

#include <iostream>
using namespace std;

#define DIM 16
texture<unsigned char,1,cudaReadModeNormalizedFloat>  texIn;


__global__ void fun(unsigned char * in, float * out)
{

	int tid = threadIdx.x + blockIdx.x * blockDim.x;
    //we can access to texture memory like normal global memory
	//out[tid] = in[tid] * 2;
	out[tid] = tex1Dfetch(texIn,tid);
}

int main()
{
unsigned char * inGlobe;
float * outGlobe;
unsigned char tmp[DIM][DIM];
float tmp2[DIM][DIM];

cudaMalloc((void**)&inGlobe,DIM * DIM  );
cudaMalloc((void**)&outGlobe,DIM * DIM * sizeof (float));
//cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
cudaBindTexture( NULL, texIn,inGlobe,                
                 DIM * DIM * sizeof (unsigned char) );
	
for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
	{
		tmp[i][j] = i * DIM + j;
		//cout << tmp[i][j] << "  " ;
	}
	//cout << endl;
}

cudaMemcpy( inGlobe, tmp, DIM * DIM, cudaMemcpyHostToDevice );    

fun<<<DIM,DIM>>>(inGlobe,outGlobe);
	
cudaMemcpy( tmp2, outGlobe, DIM * DIM * sizeof (float), cudaMemcpyDeviceToHost );

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

