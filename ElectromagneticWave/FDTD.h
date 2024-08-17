#pragma once
#include "WaveField.h"

typedef std::vector<WaveField> DataFDTD;
class FDTD
{
private: /* data */
	DataFDTD wave;
	MODE mode;

private: /* config */
	double lenx;
	double leny;
	double period;
	unsigned long long numx;
	unsigned long long numy;
	unsigned long long numt;
	
private: /* derived */
	double dx;
	double dy;
	double dt;
	double courant;

public: /* condition */
	bool setBasicCondition(const WaveField& _init, double _period);
	bool setBasicCondition(const WaveField& _init, double _period, unsigned long long _numt);

protected: /* parts */
	WaveField calcNextStepField(const WaveField& _now) const;

protected: /* virtual */
	virtual bool solve() = 0;
};