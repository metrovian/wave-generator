#pragma once
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <thread>
#include <vector>
#include <Eigen/Dense>

enum class MODE
{
	TRANSVERSE_ELECTRIC,
	TRANSVERSE_MAGNETIC,
};

typedef std::vector<std::vector<Eigen::Vector3d>> WaveData;
class WaveField
{
private: /* data */
	WaveData field;

private: /* config */
	MODE mode;
	double lenx;
	double leny;
	unsigned long long numx;
	unsigned long long numy;

private: /* derived */
	double dx;
	double dy;

private: /* status */
	bool isvalid = false;

public: /* constructor */
	WaveField(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy);

private: /* memory */
	bool mallocWaveField();
	bool check(unsigned long long _idx, unsigned long long _idy) const;

public: /* public use */
	bool setField(Eigen::Vector3d _field, unsigned long long _idx, unsigned long long _idy);
	
	Eigen::Vector3d getField(unsigned long long _idx, unsigned long long _idy) const;
	Eigen::Vector3d getPoyntingVector(unsigned long long _idx, unsigned long long _idy) const;

	double getDX() const;
	double getDY() const;
	double getLX() const;
	double getLY() const;

	unsigned long long getNX() const;;
	unsigned long long getNY() const;;
};