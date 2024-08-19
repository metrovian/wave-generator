#include "FreeSpaceFDTD.h"

Eigen::Vector3d FreeSpaceFDTD::reflectiveBoundary(const WaveField& _field, size_t _idx, size_t _jdx) const
{
    if (_idx >= numx) return _field.getField(numx - 1, _jdx);
    if (_jdx >= numy) return _field.getField(_idx, numy - 1);
    if (_jdx < 0) return _field.getField(0, _jdx);
    if (_jdx < 0) return _field.getField(_idx, 0);

    return _field.getField(_idx, _jdx);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    posx = _lenx / 2.0;
    posy = _leny / 2.0;
    sqr = _lenx / (double)_numx * 5.0;
    
    solve(_mode, _lenx, _leny, _period, _numx, _numy);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, double _posx, double _posy, double _sqr, double _famp)
{
    posx = _posx;
    posy = _posy;
    sqr = _sqr;
    famp = _famp;

    solve(_mode, _lenx, _leny, _period, _numx, _numy);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt)
{
    posx = _lenx / 2.0;
    posy = _leny / 2.0;
    sqr = _lenx / (double)_numx * 5.0;

    solve(_mode, _lenx, _leny, _period, _numx, _numy, _numt);
}

FreeSpaceFDTD::FreeSpaceFDTD(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt, double _posx, double _posy, double _sqr, double _famp)
{
    posx = _posx;
    posy = _posy;
    sqr = _sqr;
    famp = _famp;

    solve(_mode, _lenx, _leny, _period, _numx, _numy, _numt);
}

bool FreeSpaceFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy)
{
    WaveViewer viewer(1000, 1000);
    WaveField init = generateImpulseCondition(_mode, _lenx, _leny, _numx, _numy, posx, posy, sqr, famp);

    if (!setBasicCondition(init, _period)) return false;
    auto func = std::bind(&FreeSpaceFDTD::reflectiveBoundary, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1], func));
    }

    viewer.display(wave);
    return true;
}

bool FreeSpaceFDTD::solve(MODE _mode, double _lenx, double _leny, double _period, size_t _numx, size_t _numy, size_t _numt)
{
    WaveViewer viewer(1000, 1000);
    WaveField init = generateImpulseCondition(_mode, _lenx, _leny, _numx, _numy, posx, posy, sqr, famp);

    if (!setBasicCondition(init, _period, _numt)) return false;
    auto func = std::bind(&FreeSpaceFDTD::reflectiveBoundary, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1], func));
    }

    viewer.display(wave);
    return true;
}
