#include "TestFDTD.h"

bool TestFDTD::solve()
{
    return false;
}

#include "WaveViewer.h"
#include "Predefined.h"
void TestFDTD::test()
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

    std::cout << numt << std::endl;
    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1]));

    }
    
    d.display(wave);
    
}
