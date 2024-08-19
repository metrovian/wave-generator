#include "FreeSpaceFDTD.h"

Eigen::Vector3d FreeSpaceFDTD::reflectiveBoundary(const WaveField& _field, unsigned long long _idx, unsigned long long _jdx) const
{
    if (_idx >= numx) return _field.getField(numx - 1, _jdx);
    if (_jdx >= numy) return _field.getField(_idx, numy - 1);
    if (_jdx < 0) return _field.getField(0, _jdx);
    if (_jdx < 0) return _field.getField(_idx, 0);

    return _field.getField(_idx, _jdx);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy)
{
    posx = _lenx / 2.0;
    posy = _leny / 2.0;
    sqrl = _lenx / (double)_numx * 5.0;
    
    solve(_mode, _lenx, _leny, _numx, _numy);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy, double _posx, double _posy, double _sqrl, double _famp)
{
    posx = _posx;
    posy = _posy;
    sqrl = _sqrl;
    famp = _famp;

    solve(_mode, _lenx, _leny, _numx, _numy);
}

bool FreeSpaceFDTD::solve(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy)
{
    WaveViewer viewer(1000, 1000);
    WaveField init = generateImpulseCondition(_mode, _lenx, _leny, _numx, _numy, posx, posy, sqrl, famp);

    setBasicCondition(init, 1.0E-6);
    auto func = std::bind(&FreeSpaceFDTD::reflectiveBoundary, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1], func));
    }

    viewer.display(wave);
    return true;
}
