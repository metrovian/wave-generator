#pragma once
#include "WaveField.h"

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
	double calcElectricAlpha() const;
};

typedef std::vector<Dipole> DataDDA;
class DDA
{
protected: /* data */
	DataDDA data;
	Eigen::Vector2d kvec;

protected: /* condition */
	bool setDipoles(DataDDA _data);
	bool setWaveNumber(Eigen::Vector2d _kvec);

protected: /* parts */
	double calcPolarization() const;
	double calcField() const;
};