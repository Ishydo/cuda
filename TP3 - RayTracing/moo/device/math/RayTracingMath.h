#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int w, int h, Sphere* ptrDevTabSphere, uint nbSphere)
	    {
	    this->dim2 = w / 2;
	    this->ptrDevTabSphere =  ptrDevTabSphere;
	    this->nbSphere = nbSphere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	   virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {

	    uint s = 0;
	    Sphere bestSphere = ptrDevTabSphere[0];
	    int isUnder;

	    float2 myPosition;
	    myPosition.x = i;
	    myPosition.y = j;

	    float distance = 0;
	    float closestDistance = 10000;
	    float dz = 0;
	    float brightness = 0;
	    float hue = 0;
	    float hCarre = 0;
	    uint found = 0;

	    while(s < nbSphere){
		Sphere currentSphere = ptrDevTabSphere[s];
		hCarre =  currentSphere.hCarre(myPosition);

		// Si isUnder = True  => 1
		// Si isUnder = False => 0
		isUnder = (int) currentSphere.isEnDessous(hCarre);

		dz = currentSphere.dz(hCarre);
		distance = currentSphere.distance(dz);
		if(distance * isUnder < closestDistance * isUnder)
		    {
		    bestSphere = currentSphere;
		    closestDistance = distance;
		    found = 1;
		    }
		s++;
	    }
	    hCarre = bestSphere.hCarre(myPosition);
	    dz = bestSphere.dz(hCarre);
	    brightness = bestSphere.brightness(dz);
	    hue = bestSphere.hue(t);
	    ColorTools::HSB_TO_RVB(hue * found, 1, brightness * found, ptrColor);

	    }

    private:



	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;
	uint nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
