#pragma once
#include "WaveFunction.h"

typedef std::vector<std::vector<double>> DataFDTD;

class FDTD
{
protected: /* data */
	DataFDTD wave;

protected: /* parameters */
	double length;
	double period;
	double wspeed;
	unsigned long long numx;
	unsigned long long numt;

protected: /* derived */
	double dx;
	double dt;
	double courant;

protected: /* condition */
	bool setBasicCondition(double _wspeed, double _length, double _period, unsigned long long _numx, unsigned long long _numt);

public: /* public use */
	WaveFunction castWaveFunction(double _namp, double _inspt, unsigned int _srate, unsigned short _sbit);

protected: /* virtual */
	virtual bool solve() = 0;
};