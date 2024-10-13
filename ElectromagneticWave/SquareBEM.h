#pragma once
#include "BEM.h"

class SquareBEM : public BEM
{
private: /* config */
	unsigned short numa = 60;
	double rada;
	double posx;
	double posy;

public: /* constructor */
	SquareBEM(double _lenx, double _leny, size_t _numx, size_t _numy);
};