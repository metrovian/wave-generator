#include "WaveField.h"

WaveField::WaveField(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy)
{
	mode = _mode;
	numx = _numx;
	numy = _numy;
	dx = _lenx / (double)_numx;
	dy = _leny / (double)_numy;

	isvalid = mallocWaveField();
}

bool WaveField::mallocWaveField()
{
	field.resize(numx);
	for (unsigned long long i = 0; i < numx; ++i)
	{
		field.resize(numy);
	}

	return true;
}

bool WaveField::check(unsigned long long _idx, unsigned long long _idy) const
{
	if (_idx >= numx) return false;
	if (_idy >= numy) return false;

	return true;
}

bool WaveField::setField(Eigen::Vector3d _field, unsigned long long _idx, unsigned long long _idy)
{
	if (!check(_idx, _idy)) return false;

	field[_idx][_idy] = _field;
	return true;
}

Eigen::Vector3d WaveField::getField(unsigned long long _idx, unsigned long long _idy) const
{
	if (!check(_idx, _idy)) return Eigen::Vector3d(NAN, NAN, NAN);
	return field[_idx][_idy];
}

Eigen::Vector3d WaveField::getPoyntingVector(unsigned long long _idx, unsigned long long _idy) const
{
	if (!check(_idx, _idy)) return Eigen::Vector3d(NAN, NAN, NAN);

	Eigen::Vector3d electric = Eigen::Vector3d::Zero();
	Eigen::Vector3d magnetic = Eigen::Vector3d::Zero();

	if (mode == MODE::TRANSVERSE_ELECTRIC)
	{
		magnetic.head<2>() = field[_idx][_idy].head<2>();
		electric.z() = field[_idx][_idy].z();
	}

	else if (mode == MODE::TRANSVERSE_MAGNETIC)
	{
		electric.head<2>() = field[_idx][_idy].head<2>();
		magnetic.z() = field[_idx][_idy].z();
	}

	return electric.cross(magnetic);
}

double WaveField::getDX() const 
{ 
	return dx; 
}

double WaveField::getDY() const 
{ 
	return dy; 
}

double WaveField::getLX() const 
{ 
	return lenx; 
}

double WaveField::getLY() const 
{ 
	return leny; 
}

unsigned long long WaveField::getNX() const 
{ 
	return numx; 
}

unsigned long long WaveField::getNY() const 
{ 
	return numy; 
}
