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

bool StringFDTD::solve()
{
    wave[0] = generateSinCondition(length, 0.0);
    wave[1] = wave[0];
   
    setFixedEndCondition(wave[0]);
    setFixedEndCondition(wave[1]);

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

        setFixedEndCondition(wave[n + 1]);
    }

    return false;
}
