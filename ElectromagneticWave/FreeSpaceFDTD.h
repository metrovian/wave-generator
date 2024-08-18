#pragma once
#include "FDTD.h"
#include "WaveViewer.h"

class FreeSpaceFDTD : public FDTD
{
protected: /* boundary condition */
	Eigen::Vector3d reflectiveBoundary(const WaveField& _field, unsigned long long _idx, unsigned long long _jdx) const;

public: /* constructor */
	FreeSpaceFDTD();

protected: /* virtual */
	bool solve() override;
};