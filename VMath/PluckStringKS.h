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

class PluckStringEKS : public DigitalWaveguide
{
private: /* data */
	double damp = 0.5;
	double tune = 0.1;
	double dir = 0.9;
	double pos = 0.1;
	double low = 3.0;

public: /* constructor */
	PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit);
	PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, double _damp, double _tune, double _dir, double _pos, double _low);

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) override;
};