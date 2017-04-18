#include <iostream>
#include <limits.h>
#include "Grid.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "MontecarloMultiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*				Public					*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU()
{
	float a = -1.0f;
	float b = 1.0f;
	float M = 1.0f;
	int nbFlechettes = INT_MAX / 2;

	dim3 dg = dim3(64, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	dim3 db = dim3(1024, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	Grid grid(dg, db);

	MontecarloMultiGPU montecarloMultiGPU(grid, nbFlechettes, 0.001);
	float piHat = montecarloMultiGPU.run();
	cout << "Pi = " << piHat << endl;
	return true;
	//return MathTools::isEquals(pi, PI_FLOAT, 0.01f);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
