#include <cuda_runtime.h>  
    
#include <iostream>
#include "stdio.h"
#include <cuda.h>
    //#include <cudaGL.h>
    
    using namespace std;
    
    const int DIM = 16;
    texture<unsigned char,2,cudaReadModeNormalizedFloat>  texIn;
    
    __global__ void fun(unsigned char * in, float * out)
    {
        int x = threadIdx.x;
        int y = threadIdx.y;    
        int tid = threadIdx.x + threadIdx.y * blockDim.x;   
        //out[tid] = tex2D(texIn,x,y) + in[tid];
        out[tid] = tex2D(texIn,x,y)  + in[tid] + x * 10000 + y * 1000000;
    }
    
    int main()
    {
    //memory in kernel
    unsigned char * inGlobe;
    float * outGlobe;
    
    //memory in host
    unsigned char tmp1[DIM][DIM];
    float tmp[DIM][DIM];
    
    dim3 threads(DIM,DIM);
    
    cudaMalloc((void**)&inGlobe,DIM * DIM );
    cudaMalloc((void**)&outGlobe,DIM  * DIM * sizeof (float));
    
    //cudaChannelFormatDesc desc = cudaCreateChannelDesc<unsigned char>();
    cudaChannelFormatDesc desc = cudaCreateChannelDesc(16, 16, 0, 0, cudaChannelFormatKindUnsigned);

    
    cudaBindTexture2D( NULL, texIn,inGlobe,
                     desc, DIM, DIM,
                     DIM * DIM * sizeof (unsigned char) );
    //root cause is there is error, we need DIM * DIM * sizeof (char) 
        
    for (int i = 0; i < DIM; ++i)
        for (int j = 0;  j< DIM; ++j)
            tmp1[i][j] = i*16 + j;
    
    cudaMemcpy( inGlobe, tmp1, DIM * DIM * sizeof(unsigned char), cudaMemcpyHostToDevice );    
    
    fun<<<1,threads>>>(inGlobe,outGlobe);
    cudaThreadSynchronize();    
    cudaMemcpy(tmp,outGlobe,  DIM *DIM * sizeof(float), cudaMemcpyDeviceToHost );
    cudaThreadSynchronize();
    for (int i = 0; i < DIM; ++i)
    {
        for (int j = 0;  j< DIM; ++j)
        {   
            printf("%f ", tmp[i][j]);       
        }
        cout << endl;
    }
     int k;
     cin >> k;
    return 0;
    }
    











#include <cuda_runtime.h>      
#include <iostream>
#include "stdio.h"
#include <cuda.h>     
    using namespace std;
        
        const int DIM = 8;
        texture<unsigned char,2,cudaReadModeNormalizedFloat>  texIn;
        
        __global__ void fun(unsigned char * in, float * out)
        {
            int x = threadIdx.x;
            int y = threadIdx.y;    
            int tid = threadIdx.x + threadIdx.y * blockDim.x;
            printf(" %d %d %d  %d %f \n  ",x,y,tid, in[tid],tex2D(texIn,x,y));
            //out[tid] = tex2D(texIn,x,y) + in[tid];
            //out[tid] = tex2D(texIn,x,y)  + in[tid] + x * 10000 + y * 1000000;
        }
        
        int main()
        {
        //memory in kernel
        unsigned char * inGlobe;
        float * outGlobe;
        
        //memory in host
        unsigned char tmp1[DIM][DIM];
        float tmp[DIM][DIM];
        
        dim3 threads(DIM,DIM);
        
        cudaMalloc((void**)&inGlobe,DIM * DIM );
        cudaMalloc((void**)&outGlobe,DIM  * DIM * sizeof (float));
        
        //cudaChannelFormatDesc desc = cudaCreateChannelDesc<unsigned char>();
        cudaChannelFormatDesc desc = cudaCreateChannelDesc(DIM, DIM, 0, 0, cudaChannelFormatKindUnsigned);
    
        
        cudaBindTexture2D( NULL, texIn,inGlobe,
                         desc, DIM, DIM,
                         sizeof (unsigned char) );
        //root cause is there is error, we need DIM * DIM * sizeof (char) 
            
        for (int i = 0; i < DIM; ++i)
            for (int j = 0;  j< DIM; ++j)
                tmp1[i][j] = i * DIM + j ;
        
        cudaMemcpy( inGlobe, tmp1, DIM * DIM * sizeof(unsigned char), cudaMemcpyHostToDevice );    
        
        fun<<<1,threads>>>(inGlobe,outGlobe);
        //cudaThreadSynchronize();    
        cudaMemcpy(tmp,outGlobe,  DIM *DIM * sizeof(float), cudaMemcpyDeviceToHost );
        cudaThreadSynchronize();
        /*
        for (int i = 0; i < DIM; ++i)
        {
            for (int j = 0;  j< DIM; ++j)
            {   
                printf("%f ", tmp[i][j]);       
            }
            cout << endl;
        }
        */
         int k;
         cin >> k;
         cudaFree(inGlobe);
         cudaFree(outGlobe);
        return 0;
        }
        
    
    

