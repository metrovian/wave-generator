#include "BEM.h"
#include "WaveViewer.h"

Element::Element()
{
	pos = Eigen::Vector2d::Zero();
}

Element::Element(Eigen::Vector2d _pos)
{
	pos = _pos;
}

bool BEM::setElement()
{
	data.clear();
	return true;
}

bool BEM::setElement(Eigen::Vector2d _pos)
{
	data.push_back(Element(_pos));
	return true;
}

Eigen::MatrixXcd BEM::calcImpedanceMatrix() const
{
	return Eigen::MatrixXcd();
}

bool BEM::render(unsigned int _width, unsigned int _height) const
{
	WaveViewer viewer(_width, _height);
	viewer.display(wave);

	return true;
}

bool BEM::solve(double _lenx, double _leny, size_t _numx, size_t _numy)
{
	return false;
}
