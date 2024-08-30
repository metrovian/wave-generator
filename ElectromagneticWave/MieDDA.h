#pragma once
#include "DDA.h"

class MieDDA : public DDA
{
public: /* constructor */
	MieDDA();

protected: /* virtual */
	bool solve(double _lenx, double _leny, size_t _numx, size_t _numy) override;
};