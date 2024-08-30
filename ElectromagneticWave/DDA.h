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
	Eigen::Vector2d getPosition() const;
	double getElectricAlpha() const;
};

typedef std::vector<Dipole> Dipoles;
class DDA
{
protected: /* data */
	WaveField wave;
	Dipoles data;

protected: /* source */
	Eigen::Vector2d kvec;
	double famp;

protected: /* condition */
	bool setDipoles(Dipoles _data);
	bool setPlaneWave(Eigen::Vector2d _kvec, double _famp);

protected: /* parts */
	Eigen::VectorXcd calcPlaneWave() const;
	Eigen::VectorXcd calcPolarization() const;

protected: /* scatter */
	bool setScatterField(double _lenx, double _leny, size_t _numx, size_t _numy);

public: /* viewer */
	bool render(unsigned int _width, unsigned int _height) const;

protected: /* virtual */
	virtual bool solve(double _lenx, double _leny, size_t _numx, size_t _numy) = 0;
};