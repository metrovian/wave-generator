#include "FDTD.h"

bool FDTD::setBasicCondition(double _wspeed, double _length, double _period, unsigned long long _numx, unsigned long long _numt)
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
    dt = period / (double)numt;

    courant = wspeed * dt / dx;

    wave.resize(numt);
    for (auto& psi : wave)
    {
        psi.resize(numx);
    }

    assert(courant < 1.0);

    return true;
}

WaveFunction FDTD::castWaveFunction(double _namp, double _inspt, unsigned short _sbit)
{
    WaveFunction ret;
    WaveData dat;
    unsigned long long idx = (unsigned long long)((double)numx * _inspt);
    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);

    assert(idx < numx);

    for (const auto& samples : wave)
    {
        dat.push_back((short)(ramp * samples[idx]));
    }

    ret.setWaveFunction(dat, (unsigned int)(1.0 / dt), _sbit);

    return ret;
}
