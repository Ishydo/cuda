#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforCritique(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforCritique, n, "Pi OMP for critique");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforCritique(int n)
    {
    // Clean et reboot, maintenant c'est différent

    //v1
    double sum = 0;

    const double DX = 1/(double)n;


    #pragma omp parallel for // S'occupe de faire la boucle en parallèle
    for (int i = 1; i <= n; i++)
	{
	double xi = i*DX;

	#pragma omp critical (blabla)
	{
	sum += fpi(xi);
	}
	}
    return sum*DX;

    //v2
//    {
//    double sum = 0;
//
//    const double DX = 1/(double)n;
//
//    double xi;
//
//    #pragma omp parallel for private(xi) // S'occupe de faire la boucle en parallèle
//    for (int i = 1; i <= n; i++)
//	{
//	xi = i*DX;
//
//	#pragma omp critical (blabla)
//	{
//	sum += fpi(xi);
//	}
//	}
//    return sum*DX;
//    }


    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

