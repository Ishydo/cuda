#include "Montecarlo.h"

#include <iostream>
#include <curand_kernel.h>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* ptrTabDevGeneratorGM,int* ptrDevN0, float a, float b, float M, int nbFlechettes);
extern __global__ void setup_kernel_rand(curandState* tabGeneratorThread, int deviceId);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(const Grid& grid, float a, float b, float M, int nbFlechettes) :
		a(a), b(b), M(M), nbFlechettes(nbFlechettes)
{

	this->dg = grid.dg;
	this->db = grid.db;

	this->sizeOctetTabGenerator = dg.x * dg.y * dg.z * db.x * db.y * db.z * sizeof(curandState); // octet
	this->sizeOctetN0 = sizeof(int);
	this->sizeSM = db.x * db.y * db.z * sizeof(int);

	// MM
	{
		// MM (malloc Device)
		{
			HANDLE_ERROR(cudaMalloc(&ptrDevN0, sizeOctetN0));
			HANDLE_ERROR(cudaMalloc(&ptrTabDevGeneratorGM, sizeOctetTabGenerator));
		}

		// MM (memset Device)
		{
			HANDLE_ERROR(cudaMemset(ptrDevN0, 0, sizeOctetN0));
		}

		Device::lastCudaError("Montecarlo MM (end allocation)"); // temp debug
	}

	setup_kernel_rand<<<dg, db>>>(ptrTabDevGeneratorGM, Device::getDeviceId());
}

Montecarlo::~Montecarlo(void)
{
	//MM (device free)
	{
		HANDLE_ERROR(cudaFree(ptrDevN0));
		HANDLE_ERROR(cudaFree(ptrTabDevGeneratorGM));

		Device::lastCudaError("Montecarlo MM (end deallocation)"); // temp debug
	}
}

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

float Montecarlo::getPi()
{
	return this->pi;
}

void Montecarlo::run()
{
	//Device::lastCudaError("Montecarlo (before)"); // temp debug
	//Device::printCurrent();
	montecarlo<<<dg,db, sizeSM>>>(ptrTabDevGeneratorGM, ptrDevN0, a, b, M, nbFlechettes); // assynchrone
	//Device::lastCudaError("Montecarlo (after)"); // temp debug

	// Device::synchronize(); // Temp, only for printf in  GPU

	// MM (Device -> Host)
	{
		HANDLE_ERROR(cudaMemcpy(&N0, ptrDevN0, sizeOctetN0, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}

	float delta = fabsf(b - a);
	float rektArea = M * delta;
	float ratioFlechette = N0 / (float)nbFlechettes;
	pi = 2 * rektArea * ratioFlechette;
}

int Montecarlo::getCoutFlechette()
    {
    return N0;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
