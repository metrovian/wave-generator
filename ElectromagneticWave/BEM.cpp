#include "BEM.h"
#include "WaveViewer.h"
#include "Predefined.h"

Element::Element()
{
	pos = Eigen::Vector2d(0.0, 0.0);
	vec = Eigen::Vector2d(1.0, 0.0);
}

Element::Element(Eigen::Vector2d _pos, Eigen::Vector2d _vec)
{
	pos = _pos;
	vec = _vec;
}

bool BEM::setElement()
{
	data.clear();
	return true;
}

bool BEM::setElement(Eigen::Vector2d _pos, Eigen::Vector2d _vec)
{
	data.push_back(Element(_pos, _vec));
	return true;
}

bool BEM::render(unsigned int _width, unsigned int _height) const
{
	WaveViewer viewer(_width, _height);
	viewer.display(wave);

	return true;
}

bool BEM::solve(double _lenx, double _leny, size_t _numx, size_t _numy)
{
	if (_lenx == 0) return false;
	if (_leny == 0) return false;
	if (_numx == 0) return false;
	if (_numy == 0) return false;

	WaveField ret(MODE::TRANSVERSE_MAGNETIC, _lenx, _leny, _numx, _numy);

	Eigen::Vector3cd res = Eigen::Vector3cd::Zero();
	Eigen::VectorXcd cur = pinvSVD(calcImpedanceMatrix()) * calcExcitationVector();
	
	for (size_t i = 0; i < _numx; ++i)
	{
		for (size_t j = 0; j < _numy; ++j)
		{
			res = Eigen::Vector3cd::Zero();

			for (size_t k = 0; k < data.size(); ++k)
			{
				Eigen::Vector2d pos = Eigen::Vector2d(ret.getDX() * static_cast<double>(i), ret.getDY() * static_cast<double>(j));

				Eigen::Vector2d pvec = pos - data[i].pos;
				Eigen::Vector2cd jvec = cur[i] * data[i].vec;

				if (pvec.norm() > 0) res += std::complex<double>(0.0, kamp / PI / 4.0) * pvec.cross(jvec) * std::exp(std::complex<double>(0.0, -kamp * pvec.norm())) / pvec.norm();
			}

			res.x() = 0;
			res.y() = 0;

			ret.setField(res.real(), i, j);
		}
	}

	return true;
}
