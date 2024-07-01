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
	double damp = 0.300;
	double tune = 0.900;
	double dir = 0.500;
	double pos = 0.200;
	double low = 1.500;

public: /* constructor */
	PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit);
	PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, double _damp, double _tune, double _dir, double _pos, double _low);

protected: /* virtual */
	bool synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit) override;
};