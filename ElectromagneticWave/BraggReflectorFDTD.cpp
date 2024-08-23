#include "BraggReflectorFDTD.h"
#include "Predefined.h"

BraggReflectorFDTD::BraggReflectorFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    pos1 = _leny * 1.5 / 8.0;
    pos2 = _leny * 6.5 / 8.0;

    //thk1 = _leny * 1.0 / 80.0;
    //thk2 = _leny * 1.0 / 80.0;

    thk1 = C / freq / sqrt(epr1) / 4.0;
    thk2 = C / freq / sqrt(epr2) / 4.0;

    solve(_mode, _lenx, _leny, _period, _numx, _numy);
}

bool BraggReflectorFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    WaveField init = generateHuygensSource(_mode, _lenx, _leny, _numx, _numy, _lenx / 2.0, _leny / 8.0, 0.0, famp, freq);
    SpaceField med = generatePeriodicMedium(_lenx, _leny, _numx, _numy, pos1, pos2, thk1, thk2, epr1, epr2);

    if (!setBasicCondition(init, med, _period)) return false;

    for (size_t i = 1; i < numt; ++i)
    {
        WaveField refresh = calcNextStepField(wave[i - 1]);
        WaveField source = generateHuygensSource(_mode, _lenx, _leny, _numx, _numy, _lenx / 2.0, _leny / 8.0, calcElapsedTime(), famp, freq);

        wave.push_back(refresh + source);
    }

    return true;
}

bool BraggReflectorFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt)
{
    return false;
}
