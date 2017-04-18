#include "MontecarloMultiGPU.h"

#include <iostream>

#include "Device.h"

// Besoin de la classe du précédent TP (monoGPU)
#include "Montecarlo.h"

#include "reductionADD.h" // Pour la réduction additive

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#define PI 3.14159265358979323846264338327950288419716939937510

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

MontecarloMultiGPU::MontecarloMultiGPU(const Grid& grid, int nbFlechettes, float tolerance)
    {
    this->nbFlechettes = nbFlechettes;
    this->grid = grid;
    }

MontecarloMultiGPU::~MontecarloMultiGPU(void)
    {

    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

float MontecarloMultiGPU::run()
    {
    Device::lastCudaError("addVecteur (before)"); // temp debug

    //
    //working_kernel<<<dg,db, sizeOctet>>>(ptrDevGenerator, nbDart);


    int nbDevice=Device::getDeviceCount();
    int nbDartGPU = this->nbFlechettes / nbDevice;

    long sumTotal = 0;

    #pragma omp parallel for reduction(+:sumTotal)
    for(int idDevice=0; idDevice < nbDevice; idDevice++){

	cudaSetDevice(idDevice); // Set du device

	Montecarlo montecarlo(this->grid, -1.00f, 1.00f, 1.00f, nbDartGPU); // MontecarloMultiGPU avec son nombre de fléchettes en fonction du nombre de devices (
	montecarlo.run();

	sumTotal += montecarlo.getCoutFlechette();

    }

    double piHat = sumTotal * 4 * 1.00f / nbFlechettes; // TODO sumTotal * height/nbFlechettes

    return piHat;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
