#pragma once
#include "WaveField.h"

class Element
{
public: /* data */
	Eigen::Vector2d pos = Eigen::Vector2d::Zero();

public: /* constructor */
	Element();
	Element(Eigen::Vector2d _pos);
};

typedef std::vector<Element> Antenna;
class BEM
{
protected: /* data */
	WaveField wave;
	Antenna data;
};