#include "FreeSpaceFDTD.h"

Eigen::Vector3d FreeSpaceFDTD::reflectiveBoundary(const WaveField& _field, unsigned long long _idx, unsigned long long _jdx) const
{
    if (_idx >= numx) return _field.getField(numx - 1, _jdx);
    if (_jdx >= numy) return _field.getField(_idx, numy - 1);
    if (_jdx < 0) return _field.getField(0, _jdx);
    if (_jdx < 0) return _field.getField(_idx, 0);

    return _field.getField(_idx, _jdx);
}

FreeSpaceFDTD::FreeSpaceFDTD()
{
    solve();
}

bool FreeSpaceFDTD::solve()
{
    WaveViewer viewer(1000, 1000);
    WaveField init = generateImpulseCondition(MODE::TRANSVERSE_ELECTRIC, 100.0, 100.0, 512, 512, 50, 50, 1, 10);

    setBasicCondition(init, 1.0E-6);
    auto func = std::bind(&FreeSpaceFDTD::reflectiveBoundary, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1], func));
    }

    viewer.display(wave);
    return true;
}
