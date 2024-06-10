#pragma once
#include "WaveFunction.h"

class MelodyFunction
{
private: /* data */
	std::vector<double> dynamic;
	std::vector<double> pitch;
	std::vector<double> beat;

private: /* parts */
	bool isPlayable();

public: /* public use */
	WaveFunction getWaveFunction(unsigned short _srate, unsigned short _sbit, WaveFunction (*_wave)(double, double, double, unsigned short, unsigned short));

public: /* examples */
	static MelodyFunction over_the_rainbow(double _bpm);
};