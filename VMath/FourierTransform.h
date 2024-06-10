#pragma once
#include "WaveFunction.h"

#include <cmath>
#include <complex>
#include <vector>

typedef std::vector<short> FourierData;
class FourierFunction : public WaveFunction
{
protected: /* data */
	FourierData fdata;

public: /* constructor */
	FourierFunction(const FourierData& _data, unsigned short _srate, unsigned short _sbit);
	FourierFunction(const WaveFunction& _wave);

public: /* transform */
	bool fft(); // WaveData -> FourierData
	bool ifft(); // FourierData -> WaveData

public: /* filter */

};