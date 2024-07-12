#pragma once
#include "DigitalWaveguide.h"

class BowStringLP : public DigitalWaveguide
{
private: /* data */
	unsigned char band = 5;
	unsigned char num = 50;
	double modulus = 0.100;
	double pos = 0.200;
	double decay = 0.300;
	double start = 0.150;
	double end = 0.950;

public: /* constructor */
	BowStringLP(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit);

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit) override;
};