#include "WaveguideFDTD.h"

WaveguideFDTD::WaveguideFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    pos1 = _leny / 3.0;
    pos2 = _leny * 2.0 / 3.0;

    solve(_mode, _lenx, _leny, _period, _numx, _numy);
}

bool WaveguideFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    WaveField init = generatePointSource(_mode, _lenx, _leny, _numx, _numy, _lenx / 6.0, _leny / 2.0, 0.0, 1.0, 1.0E+8);
    SpaceField med = generateWaveguideMedium(_lenx, _leny, _numx, _numy, pos1, pos2, epr1, epr2);

    if (!setBasicCondition(init, med, _period)) return false;

    for (size_t i = 0; i < numt; ++i)
    {
        WaveField refresh = calcNextStepField(wave[wave.size() - 1]);
        WaveField source = generatePointSource(_mode, _lenx, _leny, _numx, _numy, _lenx / 6.0, _leny / 2.0, (double)i * dt, 1.0, 1.0E+8);

        wave.push_back(refresh + source);
    }

    return true;
}

bool WaveguideFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt)
{
    return false;
}
