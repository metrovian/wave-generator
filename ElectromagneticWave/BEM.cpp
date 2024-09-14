#include "BEM.h"

Element::Element()
{
	pos = Eigen::Vector2d::Zero();
}

Element::Element(Eigen::Vector2d _pos)
{
	pos = _pos;
}
