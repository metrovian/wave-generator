#pragma once
#include "WaveFunction.h"

typedef std::queue<short> DelayData;
class DigitalWaveguide : public WaveFunction
{
protected: /* delay */
	DelayData calcRandomDelayLine(double _namp, double _freq);

protected: /* filter */
	short passSimpleLPF(const DelayData& _data, unsigned char _pow) const;
	short passDynamicLPF(const DelayData& _data, short _prev, double _freq) const;
	short passStringDF(const DelayData& _data, double _damp) const;
	short passStringAPF(const DelayData& _data, short _prev, double _damp) const;

protected: /* batch-filter */
	DelayData passPickDirectionLPF(const DelayData& _data, double _pick) const;
	DelayData passPickPositionCF(const DelayData& _data, double _pick) const;

protected: /* virtual */
	virtual bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) = 0;
};