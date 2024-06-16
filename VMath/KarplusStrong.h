#pragma once
#include "WaveFunction.h"

class KarplusStrong
{
private: /* parts */
	static WaveFunction getNoiseBurst(double _namp, double _freq, unsigned short _srate, unsigned short _sbit);

public: /* public use */
	static WaveFunction synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit);
};