#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"

#include "MandelbrotMath.h"
#include "DomaineMath_GPU.h"

using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, const DomaineMath& domaineMath);
__device__ void workPixel(uchar4* ptrColorIJ,int i, int j,const DomaineMath& domaineMath,MandelbrotMath* ptrMandelbrotMath, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath = MandelbrotMath(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    int s = TID; // Variable de travail
    int i, j;	// Les indices lignes et colonne

    while(s < WH)
	{
	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[
	    workPixel(&ptrDevPixels[s],i,j,domaineMath,&mandelbrotMath, t);
	    s += NB_THREAD;
	}

    }



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


    /**
     * i in [0,h[
     * j in [0,w[
     *
     * code commun a:
     * 	- entrelacementOMP
     * 	- forAutoOMP
     */
    __device__
    void workPixel(uchar4* ptrColorIJ,int i, int j,const DomaineMath& domaineMath,MandelbrotMath* ptrMandelbrotMath, float t)
        {
        // (i,j) domaine ecran dans N2
        // (x,y) domaine math dans R2

        double x;
        double y;
        domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

        //float t=variateurAnimation.get();

        ptrMandelbrotMath->colorXY(ptrColorIJ,x, y, t); // in [01]
        }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

