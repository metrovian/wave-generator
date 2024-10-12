#pragma once
#include "WaveField.h"
#include "EigenMatrix.h"

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

protected: /* condition */
	bool setElement();
	bool setElement(Eigen::Vector2d _pos);

public: /* viewer */
	bool render(unsigned int _width, unsigned int _height) const;

protected: /* solver */
	bool solve(double _lenx, double _leny, size_t _numx, size_t _numy);

protected: /* virtual */
	virtual Eigen::MatrixXcd calcImpedanceMatrix() const = 0;
	virtual Eigen::VectorXcd calcExcitationVector() const = 0;
};