#ifndef SPHERE_H
#define SPHERE_H
#include "cudaTools.h"
#include "MathTools.h"
class Sphere
    {
    public:
	__host__ Sphere(float3 centre, float rayon, float hue)
	    {
// Inputs
	    this->centre = centre;
	    this->r = rayon;
	    this->hueStart = hue;
	    this->T = this->hueStart;
// Tools
	    this->rCarre = rayon * rayon;
	    }
	/**
	 * required by example for
	 new Sphere[n]
	 */
	__host__ Sphere()
	    {
// rien
	    }
	__device__
	float hCarre(float2 xySol)
	    {
	    float a = (centre.x - xySol.x);
	    float b = (centre.y - xySol.y);
	    return a * a + b * b;
	    }
	__device__
	bool isEnDessous(float hCarre)
	    {
	    return hCarre < rCarre;
	    }
	__device__
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }
	__device__
	float brightness(float dz)
	    {
	    return dz / r;
	    }
	__device__
	float distance(float dz)
	    {
	    return centre.z - dz;
	    }
	__device__
	float getHueStart()
	    {
	    return hueStart;
	    }
	__device__
	float hue(float t) // usefull for animation
	    {
	    return 0.5f + 0.5f * sinf(t + T + 3 * PI_FLOAT / 2);
	    }
    private:
// Inputs
	float r;
	float3 centre;
	float hueStart;
// Tools
	float rCarre;
	float T; // usefull for animation
    };
#endif
