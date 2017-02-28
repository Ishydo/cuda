#pragma once

#include <string>

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

// ptr fonction de type double xxx(int n)
// ou xxx sera une methode de calcul de pi
typedef double (*AlgoPI)(int);

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

double fpi(double x);
bool isAlgoPI_OK(AlgoPI algoPI, int n, string title);

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

