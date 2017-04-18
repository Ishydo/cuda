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

#include "Montecarlo.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*				Public					*|
 \*-------------------------------------*/

bool useMontecarlo()
{
	float a = -1.0f;
	float b = 1.0f;
	float M = 1.0f;
	int nbFlechettes = INT_MAX / 2;

	dim3 dg = dim3(64, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	dim3 db = dim3(1024, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	Grid grid(dg, db);

	Montecarlo montecarlo(grid, a, b, M, nbFlechettes);
	montecarlo.run();
	float pi = montecarlo.getPi();
	cout << "Pi = " << pi << endl;

	return MathTools::isEquals(pi, PI_FLOAT, 0.01f);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
