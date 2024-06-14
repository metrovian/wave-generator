#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() 
{
    //WaveFunction test = WaveFunction::sqr(0.02, 2000, 5.0, 44100, 16, 0.3);
    //FourierFunction ok(test);

    //ok.exportWaveSpectrum("spectrumtest");
    //ok.playWave();

    //ok.setLPF(3000, -3);
    //ok.playWave();

    MelodyFunction s = MelodyFunction::over_the_rainbow(120);
    std::cout << "calculating" << std::endl;

    auto func = [](double a, double b, double c)
        {
            FourierFunction X(WaveFunction::saw(a, b * pow(2.0, 7.0 / 12.0), c, 44100, 16, false));
            X.setLPF(A5, -3);
            return X;
        };

    FourierFunction k = s.getWaveFunction(func);
    std::cout << "play" << std::endl;
    k.playWave();
   
    return 0;
}
