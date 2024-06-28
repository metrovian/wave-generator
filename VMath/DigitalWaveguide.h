#pragma once
#include "WaveFunction.h"

typedef std::queue<short> DelayData;
class DigitalWaveguide : public WaveFunction
{
protected: /* delay */
	DelayData getRandomDelayLine(double _namp, double _freq);

protected: /* filter */
	short passSimpleLPF(const DelayData& _data, unsigned char _pow) const;

public: /* public use */
	virtual bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) = 0;
};