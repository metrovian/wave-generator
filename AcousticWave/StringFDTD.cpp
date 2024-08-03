#include "StringFDTD.h"
#include "Predefined.h"

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density)
{
    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
    solve();
}

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density, double _decay)
{
    decay = _decay;

    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
    solve();
}

bool StringFDTD::setBoundaryCondition(std::vector<double>& _wave) const
{
    if (_wave.size() == 0) return false;
    
    _wave[0] = 0;
    _wave[_wave.size() - 1] = 0;
}

std::vector<double> StringFDTD::generateRandomCondition() const
{
    assert(_namp > 0);

    std::vector<double> ret(numx);

    for (unsigned long long i = 1; i < numx - 1; ++i)
    {
        ret[i] = 1.0 - 2.0 * (double)rand() / (double)RAND_MAX;
    }

    setBoundaryCondition(ret);
    return ret;
}

std::vector<double> StringFDTD::generateSinCondition(double _wlen, double _phase) const
{
    assert(_namp > 0);
    assert(_freq > 0);

    std::vector<double> ret(numx);

    for (unsigned long long i = 1; i < numx - 1; ++i)
    {
        ret[i] = std::sin(2.0 * PI / _wlen * dx * (double)i + _phase);
    }

    setBoundaryCondition(ret);
    return ret;
}

std::vector<double> StringFDTD::generateImpulseCondition(double _istar, double _iend) const
{
    assert(_namp > 0);
    assert(_istar > 0 && _istar < 1.0);
    assert(_iend > 0 && _iend < 1.0);
    assert(_istar < _iend);

    std::vector<double> ret(numx);

    for (unsigned long long i = 1; i < numx - 1; ++i)
    {
        if ((double)numx * _istar < i && i < (double)numx * _iend)
        {
            ret[i] = 1.0;
        }
    }

    setBoundaryCondition(ret);
    return ret;
}

bool StringFDTD::solve()
{
    wave[0] = generateSinCondition(length, 0.0);
    wave[1] = wave[0];
   
    for (unsigned long long n = 1; n < numt - 1; ++n)
    {
        for (unsigned long long i = 1; i < numx - 1; ++i) 
        {
            wave[n + 1][i] = 0;
            wave[n + 1][i] += wave[n][i] * (2.0 + decay * dt);
            wave[n + 1][i] -= wave[n - 1][i];
            wave[n + 1][i] += courant * courant * (wave[n][i + 1] - 2.0 * wave[n][i] + wave[n][i - 1]);
            wave[n + 1][i] /= 1.0 + decay * dt;
        }

        setBoundaryCondition(wave[n + 1]);
    }

    return false;
}
