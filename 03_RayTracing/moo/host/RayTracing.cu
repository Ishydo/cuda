#include "RayTracing.h"
#include "SphereCreator.h"

#include <iostream>
#include <assert.h>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t, uint nbSphere, Sphere* ptrDevTabSphere);

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
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt, uint nbSphere) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {
    // Inputs
    this->dt = dt;
    this->nbSphere = nbSphere;

    SphereCreator sphereCreator(nbSphere, w, h);
    this->ptrTabSphere = sphereCreator.getTabSphere();
    this->sizeOctet = nbSphere * sizeof(Sphere);

    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);

    // Tools
    this->t = 0; // protected dans Animable
    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("vague rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    rayTracing<<<dg,db>>>(ptrDevPixels,w,h,t, nbSphere, ptrDevTabSphere);

    Device::lastCudaError("vague rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

