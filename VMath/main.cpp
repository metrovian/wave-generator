#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"
#include "WaveletTransform.h"
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

    MelodyFunction s = MelodyFunction::cannon(240);
    std::cout << "calculating" << std::endl;

    
    auto func = [](double a, double b, double c)
        {
            //FourierFunction X(WaveFunction::saw(a, b, c, 44100, 16, false));
            return WaveFunction::sin(a, b, c, 44100, 16);
        };

  

    FourierFunction k = s.getWaveFunction(func);
    //std::cout << "play" << std::endl;
    //k.playWave();
    //k.exportWave("cannon");
   
    MorletFunction Y(k, C4, C6, pow(2.0, 1.0 / 12.0), 0.1);
    std::cout << Y.exportWavelet("wavelettest") << std::endl;

    return 0;
}
