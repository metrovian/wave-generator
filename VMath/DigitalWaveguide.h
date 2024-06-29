#pragma once
#include "WaveFunction.h"

typedef std::queue<short> DelayData;
class DigitalWaveguide : public WaveFunction
{
protected: /* delay */
	DelayData calcRandomDelayLine(double _namp, double _freq);

protected: /* filter */
	short passSimpleLPF(const DelayData& _data, unsigned char _pow) const;
	short passDynamicLPF(const DelayData& _data, double _freq) const;

protected: /* virtual */
	virtual bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) = 0;
};