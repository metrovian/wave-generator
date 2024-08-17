#include "FDTD.h"
#include "Predefined.h"

bool FDTD::setBasicCondition(const WaveField& _init, double _period)
{
	if (_period < 0) return false;

	wave.push_back(_init);

	courant = 0.950;
	period = _period;

	dx = _init.getDX();
	dy = _init.getDY();

	numx = _init.getNX();
	numy = _init.getNY();

	dt = std::min(dx / C * courant, dy / C * courant) / sqrt(2);
	numt = (unsigned long long)(period / dt);

	return true;
}

bool FDTD::setBasicCondition(const WaveField& _init, double _period, unsigned long long _numt)
{
	if (_period < 0) return false;
	if (_numt < 0) return false;

	wave.push_back(_init);
	
	numx = _init.getNX();
	numy = _init.getNY();
	numt = _numt;

	dx = _init.getDX();
	dy = _init.getDY();
	dt = _period / (double)_numt;

	courant = C * dt * std::sqrt(1.0 / dx / dx + 1.0 / dy / dy);
	period = _period;

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
				Eigen::Vector3d ndx = now;
				Eigen::Vector3d ndy = now;

				if (i > 1) ndx = next.getField(i - 1, j);
				if (j > 1) ndy = next.getField(i, j - 1);

				now.z() += estp * ((now.y() - ndx.y()) / dx - (now.x() - ndy.x()) / dy);

				next.setField(now, i, j);
			}
		}

		for (unsigned long long i = 0; i < numx; ++i)
		{
			for (unsigned long long j = 0; j < numy; ++j)
			{
				Eigen::Vector3d now = next.getField(i, j);
				Eigen::Vector3d ndx = now;
				Eigen::Vector3d ndy = now;

				if (i + 1 < numx) ndx = next.getField(i + 1, j);
				if (j + 1 < numy) ndy = next.getField(i, j + 1);

				now.x() -= mstp * (ndy.z() - now.z()) / dy;
				now.y() += mstp * (ndx.z() - now.z()) / dx;

				next.setField(now, i, j);
			}
		}
	}

	return next;
}
