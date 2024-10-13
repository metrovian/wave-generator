#pragma once
#include "BEM.h"

class LineBEM : public BEM
{
private: /* config */
	unsigned short numa = 150;
	double lena;
	double posx;
	double posy;

public: /* constructor */
	LineBEM(double _lenx, double _leny, size_t _numx, size_t _numy);
};