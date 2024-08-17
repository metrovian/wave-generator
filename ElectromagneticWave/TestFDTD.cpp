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

    WaveField k(WaveField(MODE::TRANSVERSE_ELECTRIC, 100.0, 100.0, 100, 100));

    for (int i = 50; i < 80; ++i)
    {
        for (int j = 50; j < 80; ++j)
        {
            k.setField(Eigen::Vector3d(0, 0, 1.0), (unsigned long long)(i), (unsigned long long)(j));
        }
    }

    setBasicCondition(k, 1.0E-5);

    std::cout << numt << std::endl;
    for (int i = 0; i < numt; ++i)
    {
        wave.push_back(calcNextStepField(wave[wave.size() - 1]));
        d.display(wave[i]);
    }
    

    
}
