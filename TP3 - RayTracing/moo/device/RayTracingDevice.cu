#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"
#include "Sphere.h"

#include "IndiceTools_GPU.h"
using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		RayTracingDevice.cu et non RayTracing.cu
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

__global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t, uint nbSphere, Sphere* ptrDevTabSphere)
    {
    RayTracingMath rayTracingMath = RayTracingMath(w, h, ptrDevTabSphere, nbSphere);

    const int WH=w*h;
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i;	// in [0,h[
    int j; 	// in [0,w[

    int s = TID;  // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); 	// update (i, j)
	rayTracingMath.colorIJ(&ptrDevPixels[s],i, j, t); 	// update ptrDevPixels[s]
	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

