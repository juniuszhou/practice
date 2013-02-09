/*
this example is to show how to use pitched memory to complete
a task, that move the item in a matrix to other position.
move right 5, and move down 7.
*/
#include <iostream>
using namespace std;

static void HandleError( cudaError_t err,const char *file, int line ) {
    if (err != cudaSuccess) {
        cout <<  cudaGetErrorString(err) << file << line << endl;
        exit( EXIT_FAILURE );
    }
}
#define checkCudaErrors( err ) (HandleError( err, __FILE__, __LINE__ ))

#define NUM_REPS 100  // number of repetitions performed  
#define TILE_DIM 16   // tile/block size

texture<float, 2, cudaReadModeElementType> texRefPL;

__global__ void shiftPitchLinear(float* odata, int pitch, int width, int height, 
				 int shiftX, int shiftY)
{
  int xid = blockIdx.x * blockDim.x + threadIdx.x;
  int yid = blockIdx.y * blockDim.y + threadIdx.y;
  
  odata[yid*pitch+xid] = tex2D(texRefPL, 
			       (xid + shiftX)/(float)width, 
			       (yid + shiftY)/(float)height);
}

int
main( int argc, char** argv) 
{
  // set array size
  const int nx = 2045;  
  const int ny = 2045;

  // shifts applied to x and y data
  const int x_shift = 5;
  const int y_shift = 7;

  dim3 grid(nx/TILE_DIM, ny/TILE_DIM), threads(TILE_DIM, TILE_DIM);  
  int devID = 0;

  // CUDA events for timing
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float *h_idata = (float*) malloc(sizeof(float)*nx*ny);
  float *h_odata = (float*) malloc(sizeof(float)*nx*ny);
  float *gold = (float*) malloc(sizeof(float)*nx*ny);

  for(int i = 0; i < nx*ny; ++i) h_idata[i] = (float) i;    

  float *d_idataPL;
  //pitch size in device
  size_t d_pitchBytes;

  cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();

  checkCudaErrors(cudaMallocPitch((void**) &d_idataPL, &d_pitchBytes, nx*sizeof(float), ny));  
  cout << d_pitchBytes << endl;

  float *d_odata;
  checkCudaErrors(cudaMallocPitch( (void**) &d_odata, &d_pitchBytes, nx*sizeof(float), ny));
  cout << d_pitchBytes << endl;
  
  //here h_pitchBytes means pitch in host memory. there is not padding.
  size_t h_pitchBytes = nx*sizeof(float);

  checkCudaErrors(cudaMemcpy2D(d_idataPL, d_pitchBytes, h_idata, h_pitchBytes, 
			     nx*sizeof(float), ny, cudaMemcpyHostToDevice)); 

  texRefPL.normalized = 1;
  texRefPL.filterMode = cudaFilterModePoint;
  texRefPL.addressMode[0] = cudaAddressModeWrap;
  texRefPL.addressMode[1] = cudaAddressModeWrap;
  
  checkCudaErrors(cudaBindTexture2D(0, &texRefPL, d_idataPL, &channelDesc, nx, ny, d_pitchBytes));  
  
  checkCudaErrors(cudaMemset2D(d_odata, d_pitchBytes, 0, nx*sizeof(float), ny));
  checkCudaErrors(cudaEventRecord(start, 0));
  
  shiftPitchLinear<<<grid, threads>>>(d_odata, (int)(d_pitchBytes/sizeof(float)), nx, ny, 
					x_shift, y_shift);
 
  checkCudaErrors(cudaEventRecord(stop, 0));
  checkCudaErrors(cudaEventSynchronize(stop));
  float timePL;
  checkCudaErrors(cudaEventElapsedTime(&timePL, start, stop));  

  checkCudaErrors(cudaMemcpy2D(h_odata, h_pitchBytes, d_odata, d_pitchBytes, 
			     nx*sizeof(float), ny, cudaMemcpyDeviceToHost));
  

  checkCudaErrors(cudaMemset2D(d_odata, d_pitchBytes, 0, nx*sizeof(float), ny));
  checkCudaErrors(cudaEventRecord(start, 0));
 
  
  
  checkCudaErrors(cudaEventRecord(stop, 0));
  checkCudaErrors(cudaEventSynchronize(stop));
 
  checkCudaErrors(cudaMemcpy2D(h_odata, h_pitchBytes, d_odata, d_pitchBytes, 
		     nx*sizeof(float), ny, cudaMemcpyDeviceToHost));
  
    
  float bandwidthPL = 2.f*1000.f*nx*ny*sizeof(float)/(1.e+9f)/(timePL/NUM_REPS);
 
  printf("\nBandwidth (GB/s) for pitch linear: %.2e;\n", 
	 bandwidthPL);

  float fetchRatePL = nx*ny/1.e+6f/(timePL/(1000.0f*NUM_REPS));
 
  printf("\nTexture fetch rate (Mpix/s) for pitch linear: %.2e;\n", 
	 fetchRatePL);

  free(h_idata);
  free(h_odata);
  free(gold);

  checkCudaErrors(cudaUnbindTexture(texRefPL));
  
  checkCudaErrors(cudaFree(d_idataPL));
 
  checkCudaErrors(cudaFree(d_odata));

  checkCudaErrors(cudaEventDestroy(start));
  checkCudaErrors(cudaEventDestroy(stop));
  
  cudaDeviceReset();

  }

