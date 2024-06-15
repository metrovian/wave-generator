#pragma once
#include "FourierTransform.h"

typedef std::vector<WaveData> WaveletData;
class MorletFunction : public FourierFunction
{
private: /* data */
	WaveletData tdata;
	std::vector<double> freqs;

private: /* parts */
	double getFourierDomainMorlet(double _freq, double _treso, unsigned long long _idx);
	WaveData getMorletTransform(double _freq, double _treso);

public: /* constructor */
	MorletFunction(const FourierFunction& _wave, double _freq, double _treso);
	MorletFunction(const FourierFunction& _wave, double _freq1, double _freq2, double _freso, double _treso);

public: /* public use */
	bool exportWavelet(std::string _fname);
};