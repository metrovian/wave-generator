#pragma once
#include "FDTD.h"

class WaveguideFDTD : public FDTD
{
private: /* data */
	double epr1 = 1.00;
	double epr2 = 1.50;
	double pos1;
	double pos2;

public: /* constructor */
	WaveguideFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy);

protected: /* virtual */
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy) override;
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt) override;
};
