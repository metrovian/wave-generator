#pragma once
#include "FDTD.h"
#include "WaveViewer.h"

class FreeSpaceFDTD : public FDTD
{
private: /* data */
	double posx;
	double posy;
	double sqrl;
	double famp = 1.0;

protected: /* boundary condition */
	Eigen::Vector3d reflectiveBoundary(const WaveField& _field, unsigned long long _idx, unsigned long long _jdx) const;

public: /* constructor */
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy);
	FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy, double _posx, double _posy, double _sqrl, double _famp);

protected: /* virtual */
	bool solve(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy) override;
};