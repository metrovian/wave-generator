#pragma once
#include "FDTD.h"

class FreeSpaceFDTD : public FDTD
{
private: /* data */
	double posx;
	double posy;
	double sqr;
	double famp = 1.0;

public: /* constructor */
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy);
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, double _posx, double _posy, double _sqr, double _famp);
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt);
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt, double _posx, double _posy, double _sqr, double _famp);

protected: /* virtual */
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy) override;
	bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt) override;
};