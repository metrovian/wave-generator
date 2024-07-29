#pragma once
#include "WaveFunction.h"

typedef std::vector<std::vector<double>> DataFDTD;

class FDTD
{
private: /* data */
	DataFDTD wave;

private: /* config */
	unsigned long long numx;
	unsigned long long numt;
};