#pragma once
#include "FDTD.h"

class StringFDTD : public FDTD
{
private: /* parameters */
	double decay = 10.0;

public: /* constructor */
	StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density);
	StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density, double _decay);

private: /* boundary condition */
	bool setBoundaryCondition(std::vector<double>& _wave) const;

public: /* initial condition */
	std::vector<double> generateRandomCondition() const;
	std::vector<double> generateSinCondition(double _wlen, double _phase) const;
	std::vector<double> generateImpulseCondition(double _istar, double _iend) const;

protected: /* public use */
	bool solve() override;
};