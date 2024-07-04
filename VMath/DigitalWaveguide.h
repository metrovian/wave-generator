#pragma once
#include "WaveFunction.h"

typedef std::queue<short> DelayData;
class DigitalWaveguide : public WaveFunction
{
protected: /* parts */
	WaveData extractFrontData(const DelayData& _data) const;
	WaveData extractFrontData(const DelayData& _data, unsigned long long _count) const;

protected: /* delay */
	DelayData calcRandomDelayLine(double _namp, double _freq);
	DelayData calcBandLimDelayLine(double _namp, double _freq, unsigned char _band);

protected: /* filter */
	short passSimpleLPF(const DelayData& _data, unsigned char _pow) const;
	short passDynamicLPF(const DelayData& _data, short _prev, double _freq) const;
	short passStringDF(const DelayData& _data, double _damp) const;
	short passStringAPF(const DelayData& _data, short _prev, double _damp) const;
	short passLPCF(const DelayData& _data) const;

protected: /* batch-filter */
	DelayData passPickDirectionLPF(const DelayData& _data, double _dir) const;
	DelayData passStringPositionCF(const DelayData& _data, double _pos) const;

public: /* public use */
	WaveFunction castWaveFunction();

protected: /* virtual */
	virtual bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) = 0;
};