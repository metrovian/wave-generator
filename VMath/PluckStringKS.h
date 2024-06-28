#pragma once
#include "DigitalWaveguide.h"

class PluckStringKS : public DigitalWaveguide
{
private: /* data */
	unsigned char pow = 2;

public: /* constructor */
	PluckStringKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit);
	PluckStringKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, unsigned char _pow);

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) override;
};