#include "FDTD.h"

bool FDTD::setBasicCondition(double _length, double _period, double _wspeed, unsigned long long _numx, unsigned long long _numt)
{
    if (_length < 0) return false;
    if (_period < 0) return false;
    if (_wspeed < 0) return false;
    if (_numx == 0) return false;
    if (_numt == 0) return false;
    
    length = _length;
    period = _period;
    wspeed = _wspeed;
    numx = _numx;
    numt = _numt;

    dx = length / (double)numx;
    dt = length / (double)numt;

    courant = wspeed * dt / dx;

    return true;
}
