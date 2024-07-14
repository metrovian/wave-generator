#pragma once
#include "DigitalWaveguide.h"

class HammerStringCM : public DigitalWaveguide
{
public: /* constructor */
	HammerStringCM(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit);

protected: /* protected */
	bool synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit) override;
};