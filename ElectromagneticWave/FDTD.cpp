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
	numt = (size_t)(period / dt);

	return true;
}

bool FDTD::setBasicCondition(const WaveField& _init, double _period, size_t _numt)
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

WaveField FDTD::generateImpulseCondition(MODE _mode, double _lenx, double _leny, size_t _numx, size_t _numy, double _posx, double _posy, double _sqrl, double _famp)
{
	WaveField ret(_mode, _lenx, _leny, _numx, _numy);

	size_t idx = static_cast<size_t>(_numx * (_posx / _lenx));
	size_t jdx = static_cast<size_t>(_numy * (_posy / _leny));
	size_t sqrx = static_cast<size_t>(_numx * (_sqrl / _lenx / 2.0));
	size_t sqry = static_cast<size_t>(_numy * (_sqrl / _leny / 2.0));

	if (idx - sqrx < 0) return ret;
	if (jdx - sqry < 0) return ret;
	if (idx + sqrx >= _numx) return ret;
	if (jdx + sqry >= _numy) return ret;

	for (size_t i = idx - sqrx; i < idx + sqrx; ++i)
	{
		for (size_t j = jdx - sqry; j < jdx + sqry; ++j)
		{
			ret.setField(Eigen::Vector3d(0, 0, _famp), i, j);
		}
	}

	return ret;
}

WaveField FDTD::calcNextStepField(const WaveField& _now, const std::function<Eigen::Vector3d(const WaveField& _field, size_t _idx, size_t _jdx)>& _inspect) const
{
	WaveField next = _now;

	double estp = dt / EP;
	double mstp = dt / MU;

	if (mode == MODE::TRANSVERSE_ELECTRIC)
	{
		for (size_t i = 0; i < numx; ++i)
		{
			for (size_t j = 0; j < numy; ++j)
			{
				Eigen::Vector3d now = _inspect(next, i, j);
				Eigen::Vector3d ndx = _inspect(next, i - 1, j);
				Eigen::Vector3d ndy = _inspect(next, i, j - 1);

				now.z() += estp * ((now.y() - ndx.y()) / dx - (now.x() - ndy.x()) / dy);

				next.setField(now, i, j);
			}
		}

		for (size_t i = 0; i < numx; ++i)
		{
			for (size_t j = 0; j < numy; ++j)
			{
				Eigen::Vector3d now = _inspect(next, i, j);
				Eigen::Vector3d ndx = _inspect(next, i + 1, j);
				Eigen::Vector3d ndy = _inspect(next, i, j + 1);

				now.x() -= mstp * (ndy.z() - now.z()) / dy;
				now.y() += mstp * (ndx.z() - now.z()) / dx;

				next.setField(now, i, j);
			}
		}
	}

	return next;
}
