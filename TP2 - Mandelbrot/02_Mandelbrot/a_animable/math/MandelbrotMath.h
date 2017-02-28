#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, 120), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    //float z = f(x, y, t);

	    // Pour Mandelbrot, besoin de x, y et n qui est t

	    int k = 0;	// L'itération

	    float a = 0;
	    float b = 0;

	    while(k <= t && (a*a) + (b*b) <= 4){
		float aCopy = a;
		a = (a*a - b*b) + x;
		b = 2 * aCopy * b + y;
		k++;
	    }



	    if(k > t)
		{ // Du noir
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float s = (float)k;
		calibreur.calibrer(s);
		float hue01 = s;
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}



	    ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, float t)
	    {
	    return sin(x * n + t) * cos(y * n + t);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
