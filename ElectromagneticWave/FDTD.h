#pragma once
#include "WaveField.h"

typedef std::vector<WaveField> DataFDTD;
typedef std::vector<std::vector<double>> SpaceFDTD;
class FDTD
{
protected: /* data */
	DataFDTD wave;
	SpaceFDTD medium;
	MODE mode;

protected: /* config */
	double lenx;
	double leny;
	double period;
	size_t numx;
	size_t numy;
	size_t numt;
	
protected: /* derived */
	double dx;
	double dy;
	double dt;
	double courant;

public: /* condition */
	bool setBasicCondition(const WaveField& _init, double _period);
	bool setBasicCondition(const WaveField& _init, double _period, size_t _numt);
	bool setBasicCondition(const WaveField& _init, const SpaceFDTD& _medium, double _period);
	bool setBasicCondition(const WaveField& _init, const SpaceFDTD& _medium, double _period, size_t _numt);

public: /* source */
	static WaveField generateImpulseCondition(MODE _mode, double _lenx, double _leny, size_t _numx, size_t _numy, double _posx, double _posy, double _sqrl, double _famp);

public: /* medium */
	static SpaceFDTD generateDefaultMedium(size_t _numx, size_t _numy);

public: /* field viewer */
	bool render(unsigned int _width, unsigned int _height);

protected: /* parts */
	WaveField calcNextStepField(const WaveField& _now, const std::function<Eigen::Vector3d(const WaveField& _field, size_t _idx, size_t _jdx)>& _inspect) const;

protected: /* virtual */
	virtual bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy) = 0;
	virtual bool solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt) = 0;
};