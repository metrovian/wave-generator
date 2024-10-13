#include "SquareBEM.h"
#include "Predefined.h"

SquareBEM::SquareBEM(double _lenx, double _leny, size_t _numx, size_t _numy)
{
    rada = 0.25 / kamp;
    posx = _lenx / 2.0;
    posy = _leny / 2.0;

    for (unsigned short i = 0; i < numa; ++i)
    {
        double phi = PI * 2.0 * static_cast<double>(i) / static_cast<double>(numa);

        double eosx = posx + rada * std::cos(phi);
        double eosy = posy + rada * std::sin(phi);

        setElement(Eigen::Vector2d(eosx, eosy), Eigen::Vector2d(std::cos(phi), std::sin(phi)));
    }

    solve(_lenx, _leny, _numx, _numy);
}