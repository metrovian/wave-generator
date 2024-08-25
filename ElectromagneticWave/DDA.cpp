#include "DDA.h"

Dipole::Dipole()
{
	pos = Eigen::Vector2d::Zero();
	epr = 1.0;
	area = 1.0;
}

Dipole::Dipole(Eigen::Vector2d _pos, double _epr, double _area)
{
	pos = _pos;
	epr = _epr;
	area = _area;
}

double Dipole::calcElectricAlpha(SHAPE _shape) const
{
	return 0.0;
}
