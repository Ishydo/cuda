#pragma once

#include "cudaTools.h"

#include "Provider_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Observation:
 * 	Les objets retournees sont sur le tas (2 ptr)
 *
 * Destruction:
 * 	4 cas d'utilisation:
 * 		- Image
 * 		- Animable
 * 		- ForceBrut
 * 		- Barivox
 *
 * 	Cas Image:
 * 		Le viewer s'occupe d'effacer:
 * 			- Image_I*
 * 			- Animable_I<uchar4>*
 * 	Cas Animable:
 *		L'animator detruit animable
 *
 * 	Cas ForceBrut:
 * 		Force brut utilise animator qui detruit animable
 *
 * 	Cas Barivox:
 * 		Barivox detruit
 *
 * 	Autre cas:
 * 		A vous de detruire les objets
 *
 */
class RayTracingProvider: public Provider_I<uchar4>
    {
    public:

	virtual ~RayTracingProvider()
	    {
	    // Rien
	    }

	/*--------------------------------------*\
	 |*		Override		*|
	 \*-------------------------------------*/

	virtual Animable_I<uchar4>* createAnimable(void);

	virtual Image_I* createImageGL(void);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

