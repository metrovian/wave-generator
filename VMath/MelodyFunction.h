#pragma once
#include <map>
#include "WaveFunction.h"

class MelodyFunction
{
private:
	std::map<double, WaveFunction> sampler;
};