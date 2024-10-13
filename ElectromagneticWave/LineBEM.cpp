#include "LineBEM.h"
#include "Predefined.h"

LineBEM::LineBEM(double _lenx, double _leny, size_t _numx, size_t _numy)
{
    lena = PI / kamp;
    posx = _lenx / 2.0;
    posy = _leny / 2.0;

    for (unsigned short i = 0; i < numa; ++i)
    {
        double eosy = posy + lena - 2.0 * lena * static_cast<double>(i) / static_cast<double>(numa);

        setElement(Eigen::Vector2d(posx, eosy), Eigen::Vector2d(0.0, 1.0));
    }
    
    solve(_lenx, _leny, _numx, _numy);
}