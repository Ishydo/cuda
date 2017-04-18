#include "Indice1D.h"
#include "cudaTools.h"

#include <stdio.h>
#include <curand_kernel.h>
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(curandState* ptrTabDevGeneratorGM, int* ptrDevN0, int nbFlechettes);
__global__ void setup_kernel_rand(curandState* tabGeneratorThread, int deviceId);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reduceIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM, float a, float b, float M, int nbFlechettes);
static __device__ float f(float x);
static __device__ float toAB(float x, float a, float b);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* ptrTabDevGeneratorGM, int* ptrDevN0, float a, float b, float M, int nbFlechettes)
{
	extern __shared__ int tabSM[];
	reduceIntraThread(tabSM, ptrTabDevGeneratorGM, a, b, M, nbFlechettes);
	__syncthreads();
	reductionADD<int>(tabSM, ptrDevN0);
}

__global__ void setup_kernel_rand(curandState* tabGeneratorThread, int deviceId)
{
	const int tid = Indice1D::tid();
	//Customisation du generator: Proposition (au lecteur de faire mieux)
	// Contrainte : Doit etre différent d'un GPU à l'autre
	int deltaSeed = deviceId * INT_MAX/10000;
	int deltaSequence = deviceId * 100;
	int deltaOffset = deviceId * 100;
	int seed = 1234 + deltaSeed;
	int sequenceNumber = tid + deltaSequence;
	int offset = deltaOffset;
	curand_init(seed, sequenceNumber, offset, &tabGeneratorThread[tid]);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reduceIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM, float a, float b, float M, int nbFlechettes)
{
	const int NB_THREAD = Indice1D::nbThread();
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocal();

	int s = TID;

	int sumThread = 0;
	curandState localState = ptrTabDevGeneratorGM[TID];

	while (s < nbFlechettes)
	{
		float x = toAB(curand_uniform(&localState), a, b);
		float y = toAB(curand_uniform(&localState), 0.0f, M);
		if(y < f(x))
		{
			sumThread++;
		}
		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = sumThread;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
__device__ float toAB(float x, float a, float b)
{
	return (b - a) / 1.0f * x + a;
}

__device__ float f(float x)
{
	return sqrtf(1.0f - x * x);
}
