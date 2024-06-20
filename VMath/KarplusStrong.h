#pragma once
#include "WaveFunction.h"

class KarplusStrong
{
private: /* parts */
	static WaveFunction getNoiseBurst(double _namp, double _freq, unsigned short _srate, unsigned short _sbit);

public: /* public use */
	static WaveFunction synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, short (*_decay)(WaveData, unsigned long long, unsigned long long, double), double _drate);

	static short decayMoveAverage(WaveData _data, unsigned long long _idx, unsigned long long _unit, double _drate);
	static short decayTimeExponential(WaveData _data, unsigned long long _idx, unsigned long long _unit, double _drate);
};