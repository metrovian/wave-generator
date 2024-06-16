#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"
#include "WaveletTransform.h"
#include "KarplusStrong.h"
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

    //MelodyFunction s = MelodyFunction::cannon(240);
    MelodyFunction s = MelodyFunction::over_the_rainbow(150);
    std::cout << "calculating" << std::endl;

    
    auto func = [](double a, double b, double c)
        {
            //FourierFunction X(WaveFunction::saw(a, b, c, 44100, 16, false));
            //return WaveFunction::tri(a, b, c, 44100, 16);
            return KarplusStrong::synthesis(a, b, c, 44100, 16);
        };

  

    WaveFunction k = s.getWaveFunction(func);
    std::cout << "play" << std::endl;
    k.playWave();
    k.exportWave("cannon");
   
    //MorletFunction Y(k, G3, D5, pow(2.0, 1.0 / 12.0), 0.1);
    //std::cout << Y.exportWavelet("wavelettest") << std::endl;


    //WaveFunction S;
    //S.importWave("440");
    //FourierFunction F(S);
    //MorletFunction G(F, A2, A5, pow(2.0, 1.0/12.0), 1.0);
    //G.exportWaveletSpectrum("test2");

    //FourierFunction X(A);
    //MorletFunction Y(X, A3, A5, pow(2.0, 1.0 / 12.0), 1.0);
    //Y.exportWaveletSpectrum("KS-TEST");

    return 0;
}
