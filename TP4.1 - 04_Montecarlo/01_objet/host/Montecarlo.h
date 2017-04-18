
#pragma once

#include "cudaTools.h"
#include <curand_kernel.h>
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
{
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

public:

	/**
	 * update w by v1+v2
	 */
	Montecarlo(const Grid& grid, float a, float b, float M, int nbFlechettes);

	virtual ~Montecarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

public:

	void run();
	float getPi();
	int getCoutFlechette();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

private:

	// Inputs
	float a;
	float b;
	float M;
	int nbFlechettes;

	// Outputs
	float pi;

	// Tools
	dim3 dg;
	dim3 db;
	int N0;
	int* ptrDevN0;
	curandState* ptrTabDevGeneratorGM;
	size_t sizeOctetN0;
	size_t sizeOctetTabGenerator;
	size_t sizeSM;
};

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
