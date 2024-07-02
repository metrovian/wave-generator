#pragma once
#include "DigitalWaveguide.h"

class BowStringLP : public DigitalWaveguide
{
private: /* data */
	unsigned char band = 15;
	double pos = 0.200;

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) override;
};