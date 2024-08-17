#include "FDTD.h"
#include "Predefined.h"

bool FDTD::setBasicCondition(const WaveField& _init, double _period)
{
	if (_period < 0) return false;

	courant = 0.950;

	dx = _init.getDX();
	dy = _init.getDY();

	numx = _init.getNX();
	numy = _init.getNY();

	dt = std::min(dx / C * courant, dy / C * courant);
	numt = (unsigned long long)(period / dt);

	return true;
}

bool FDTD::setBasicCondition(const WaveField& _init, double _period, unsigned long long _numt)
{
	if (_period < 0) return false;
	if (_numt < 0) return false;

	numx = _init.getNX();
	numy = _init.getNY();
	numt = _numt;

	dx = _init.getDX();
	dy = _init.getDY();
	dt = _period / (double)_numt;

	courant = std::max(C * dt / dx, C * dt / dy);

	if (courant < 1.0) return true;
	return false;
}

WaveField FDTD::calcNextStepField(const WaveField& _now) const
{
	WaveField next = _now;

	double estp = dt / EP;
	double mstp = dt / MU;

	if (mode == MODE::TRANSVERSE_ELECTRIC)
	{
		for (unsigned long long i = 0; i < numx; ++i)
		{
			for (unsigned long long j = 0; j < numy; ++j)
			{
				Eigen::Vector3d now = next.getField(i, j);
				Eigen::Vector3d ndx = next.getField(i + 1, j);
				Eigen::Vector3d ndy = next.getField(i, j + 1);

				now.z() += estp * ((ndx.y() - now.y()) / dx - (ndy.x() - ndy.x()) / dy);

				next.setField(now, i, j);
			}
		}

		for (unsigned long long i = 0; i < numx; ++i)
		{
			for (unsigned long long j = 0; j < numy; ++j)
			{
				Eigen::Vector3d now = next.getField(i, j);
				Eigen::Vector3d ndx = next.getField(i + 1, j);
				Eigen::Vector3d ndy = next.getField(i, j + 1);

				now.x() -= mstp * (ndy.z() - now.z()) / dy;
				now.y() += mstp * (ndx.z() - now.z()) / dx;

				next.setField(now, i, j);
			}
		}
	}

	return next;
}
