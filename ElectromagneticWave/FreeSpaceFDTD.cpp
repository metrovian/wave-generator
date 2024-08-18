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
    WaveViewer d(1000, 1000);

    WaveField k(WaveField(MODE::TRANSVERSE_ELECTRIC, 100.0, 100.0, 512, 512));

    for (int i = 250; i < 260; ++i)
    {
        for (int j = 250; j < 260; ++j)
        {
            k.setField(Eigen::Vector3d(0, 0, 1.0), (unsigned long long)(i), (unsigned long long)(j));
            //k.setField(Eigen::Vector3d(0, 0, sin((double)i*0.1)), (unsigned long long)(i), (unsigned long long)(j));
        }
    }

    setBasicCondition(k, 1.0E-7);
    auto func = std::bind(&FreeSpaceFDTD::reflectiveBoundary, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1], func));

    }

    d.display(wave);
    return false;
}
