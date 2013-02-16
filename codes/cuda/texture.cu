/*
one dimension float texture with integet index access.
it is OK.
*/
#include <iostream>
using namespace std;
    
#define DIM 16
    texture<float>  texIn;
    texture<float>  texOut;
    texture<float>  texConstSrc;
    
    __global__ void fun(float * in, float * out)
    {
    
        int tid = threadIdx.x + blockIdx.x * blockDim.x;
        //we can access to texture memory like normal global memory
        //out[tid] = in[tid] * 2;
        out[tid] = tex1Dfetch(texIn,tid) * 5;
    }
    
    int main()
    {
    float * inGlobe;
    float * outGlobe;
    float tmp[DIM][DIM];
    
    cudaMalloc((void**)&inGlobe,DIM * DIM * 4 );
    cudaMalloc((void**)&outGlobe,DIM * DIM * 4);
    //cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
    cudaBindTexture( NULL, texIn,inGlobe,                
                     DIM * DIM * sizeof (float) );
        
    for (int i = 0; i < DIM; ++i)
    {
        for (int j = 0; j < DIM; ++j)
        {
            tmp[i][j] = i + j + 0.125;
            cout << tmp[i][j] << "  " ;
        }
        cout << endl;
    }
    
    cudaMemcpy( inGlobe, tmp, DIM * DIM * 4, cudaMemcpyHostToDevice );    
    
    fun<<<DIM,DIM>>>(inGlobe,outGlobe);
        
    cudaMemcpy( tmp, outGlobe, DIM * DIM * 4, cudaMemcpyDeviceToHost );
    
    for (int i = 0; i < DIM; ++i)
    {
        for (int j = 0; j < DIM; ++j)
            cout << tmp[i][j] << "  " ;
        cout << endl;
    }
     int k;
     cin >> k;
    return 0;
    }




/*
two dimension float texture with integet index access.
it is OK.
*/


#include <iostream>
using namespace std;

#define DIM 16
texture<float,2>  texIn;
texture<float,2>  texOut;
texture<float,2>  texConstSrc;

__global__ void fun(float * in, float * out)
{

	int tid = threadIdx.x + blockIdx.x * blockDim.x;
    //we can access to texture memory like normal global memory
	//out[tid] = in[tid] * 2;
	out[tid] = tex2D(texIn,threadIdx.x,blockIdx.x) * 3;
}

int main()
{
float * inGlobe;
float * outGlobe;
float tmp[DIM][DIM];

cudaMalloc((void**)&inGlobe,DIM * DIM * 4 );
cudaMalloc((void**)&outGlobe,DIM * DIM * 4);
cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
cudaBindTexture2D( NULL, texIn,inGlobe,
                 desc, DIM, DIM,
                 DIM * sizeof (float) );
	
for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
	{
		tmp[i][j] = i + j;
		cout << tmp[i][j] << "  " ;
	}
	cout << endl;
}

cudaMemcpy( inGlobe, tmp, DIM * DIM * 4, cudaMemcpyHostToDevice );    

fun<<<DIM,DIM>>>(inGlobe,outGlobe);
	
cudaMemcpy( tmp, outGlobe, DIM * DIM * 4, cudaMemcpyDeviceToHost );

for (int i = 0; i < DIM; ++i)
{
	for (int j = 0; j < DIM; ++j)
		cout << tmp[i][j] << "  " ;
	cout << endl;
}
 int k;
 cin >> k;
return 0;
}

