#pragma once
#include "WaveField.h"

enum class SHAPE
{
	CIRCLE,
	RECTANGLE,
};

class Dipole
{
private: /* data */
	Eigen::Vector2d pos;
	double epr;
	double area;

public: /* constructor */
	Dipole();
	Dipole(Eigen::Vector2d _pos, double _epr, double _area);

public: /* public use */
	double calcElectricAlpha(SHAPE _shape) const;
};

typedef std::vector<Dipole> DataDDA;
class DDA
{
protected: /* data */
	DataDDA data;
};