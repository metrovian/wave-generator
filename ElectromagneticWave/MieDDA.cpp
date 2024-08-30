#include "MieDDA.h"

MieDDA::MieDDA()
{
	solve(0, 0, 0, 0);
}

bool MieDDA::solve(double _lenx, double _leny, size_t _numx, size_t _numy)
{
	setPlaneWave(Eigen::Vector2d(10.0, 0), 10.0);

	Dipoles set;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			set.push_back(Dipole(Eigen::Vector2d(50 + i, 50 + j), 10, 10));
		}
	}

	setDipoles(set);
	setScatterField(100.0, 100.0, 500, 500);

	render(1000, 1000);

	return true;
}
