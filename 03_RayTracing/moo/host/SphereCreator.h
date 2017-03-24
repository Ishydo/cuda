#pragma once
#include "Sphere.h"
class SphereCreator
    {
	/*--------------------------------------*\
|*
	 Constructor
	 *|
	 \*-------------------------------------*/
    public:
	SphereCreator(int nbSpheres, int w, int h, int bord = 200);
	virtual ~SphereCreator(void);
	/*--------------------------------------*\
|*
	 Methodes
	 *|
	 \*-------------------------------------*/
    public:
	Sphere* getTabSphere();
    private:
	void createSphere(void);
	/*--------------------------------------*\
|*
	 Attributs
	 *|
	 \*-------------------------------------*/
    private:
// Inputs
	int nbSpheres;
	int w;
	int h;
	int bord;
// Tools
	Sphere* tabSphere;
    };
