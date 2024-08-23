#pragma once
#include "FDTD.h"

class BraggReflectorFDTD : public FDTD
{
private: /* data */
	double epr1 = 1.0;
	double epr2 = 1.57 * 1.57;
	double pos1;
	double pos2;
	double thk1;
	double thk2;
	double famp = 1.00;
	double freq = 1.0E+8;

public: /* constructor */
	BraggReflectorFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy);

protected: /* virtual */
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy) override;
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt) override;
};