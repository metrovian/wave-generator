#pragma once
#include "DDA.h"

class MieDDA : public DDA
{
private: /* data */
	Dipoles units;

private: /* config */
	unsigned char numd = 4;
	double lend;
	double posx;
	double posy;

public: /* constructor */
	MieDDA(double _lenx, double _leny, size_t _numx, size_t _numy);
	MieDDA(double _lenx, double _leny, size_t _numx, size_t _numy, double _kvex, double _kvey, double _famp);
	MieDDA(double _lenx, double _leny, size_t _numx, size_t _numy, unsigned char _numd, double _lend, double _posx, double _posy);
	MieDDA(double _lenx, double _leny, size_t _numx, size_t _numy, unsigned char _numd, double _lend, double _posx, double _posy, double _kvex, double _kvey, double _famp);

protected: /* virtual */
	bool solve(double _lenx, double _leny, size_t _numx, size_t _numy) override;
};