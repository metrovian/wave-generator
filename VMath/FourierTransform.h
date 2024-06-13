#pragma once
#include "WaveFunction.h"

#include <cmath>
#include <complex>
#include <vector>

typedef std::vector<std::complex<double>> FourierData;
class FourierFunction : public WaveFunction
{
protected: /* data */
	FourierData fdata;

public: /* constructor */
	FourierFunction(const FourierData& _data, unsigned short _srate, unsigned short _sbit);
	FourierFunction(const WaveFunction& _wave);

public: /* transform */
	bool fft();
	bool ifft();

public: /* filter */

};