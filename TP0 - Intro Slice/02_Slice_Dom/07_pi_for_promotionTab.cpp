#include <omp.h>
#include "MathTools.h"
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

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread,int n);
static void syntaxeFull(double* tabSumThread,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {

    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double sum = 0;
    const double DX = 1/(double)n;

    double* tabSum = new double[NB_THREAD]; // Ce tableau est sur le tas

    #pragma omp parallel for // Initialisation du tableau de manière parallèle
    for(int i=0;i<NB_THREAD;i++)
	{
	    tabSum[i] = 0;
	}

    #pragma omp parallel for // S'occupe de faire la boucle en parallèle
    for (int i = 1; i <= n; i++)
	{

	const int TID = OmpTools::getTid();
	int s = TID;


	double xi = i*DX;
	tabSum[TID] += fpi(xi);

	}

    // Réduction additive séquentielle
    double globalSum = 0;
    for(int i=0;i<NB_THREAD;i++)
	{
	    globalSum += tabSum[i];
	}

    delete[] tabSum;

    return sum*DX;


    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

