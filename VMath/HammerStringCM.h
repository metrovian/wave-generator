#pragma once
#include "DigitalWaveguide.h"

class HammerStringCM : public DigitalWaveguide
{
	bool synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit) override;
};