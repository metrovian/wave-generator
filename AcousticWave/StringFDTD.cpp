#include "StringFDTD.h"
#include "Predefined.h"

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density)
{
    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
}

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density, double _decay)
{
    decay = _decay;
    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
}

std::vector<double> StringFDTD::generateRandomCondition(double _namp)
{
    assert(_namp > 0);

    std::vector<double> ret(numx);

    for (unsigned long long i = 0; i < numx; ++i)
    {
        ret[i] = _namp * (double)rand() / (double)RAND_MAX;
    }

    return ret;
}

std::vector<double> StringFDTD::generateSinCondition(double _namp, double _freq, double _phase)
{
    assert(_namp > 0);
    assert(_freq > 0);

    std::vector<double> ret(numx);

    for (unsigned long long i = 0; i < numx; ++i)
    {
        ret[i] = _namp * std::sin(2.0 * PI * _freq * dx * (double)i + _phase);
    }

    return ret;
}

std::vector<double> StringFDTD::generateImpulseCondition(double _namp, double _istar, double _iend)
{
    assert(_namp > 0);
    assert(_istar > 0 && _istar < 1.0);
    assert(_iend > 0 && _iend < 1.0);
    assert(_istar < _iend);

    std::vector<double> ret(numx);

    for (unsigned long long i = 0; i < numx; ++i)
    {
        if ((double)numx * _istar < i && i < (double)numx * _iend)
        {
            ret[i] = _namp;
        }
    }

    return ret;
}

bool StringFDTD::solve()
{
    return false;
}
