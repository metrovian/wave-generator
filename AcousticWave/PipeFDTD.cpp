#include "PipeFDTD.h"
#include "Predefined.h"

PipeFDTD::PipeFDTD(double _length, double _period, unsigned long long _numt)
{
    setBasicCondition(SONIC, _length, _period, _numt);
    solve();
}

PipeFDTD::PipeFDTD(double _length, double _period, unsigned long long _numt, double _sonic, double _decay)
{
    decay = _decay;

    setBasicCondition(_sonic, _length, _period, _numt);
    solve();
}

bool PipeFDTD::solve()
{
    wave[0] = generateImpulseCondition(0.7, 1.0);
    wave[1] = wave[0];

    setFreeEndCondition(wave[0]);
    setFreeEndCondition(wave[1]);

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

        setFreeEndCondition(wave[n + 1]);
    }

    return true;
}
