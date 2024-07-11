#pragma once
#include "DigitalWaveguide.h"

class BowStringLP : public DigitalWaveguide
{
private: /* data */
	unsigned char band = 100;
	unsigned char num = 40;
	double pos = 0.200;

public: /* constructor */
	BowStringLP(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit);

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit) override;
};