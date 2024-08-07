#pragma once
#include "FDTD.h"

class HornFDTD : public FDTD
{
private: /* parameters */
	double decay = 1.0;

public: /* constructor */
	HornFDTD(double _length, double _period, unsigned long long _numt);
	HornFDTD(double _length, double _period, unsigned long long _numt, double _sonic, double _decay);
	HornFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt);
	HornFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _sonic, double _decay);

protected: /* virtual */
	bool solve() override;
};