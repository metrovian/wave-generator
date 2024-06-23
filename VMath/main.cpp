#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"
#include "WaveletTransform.h"
#include "KarplusStrong.h"
#include "FrequencyModulation.h"
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

    
    //auto func = [](double a, double b, double c)
    //    {
    //        //FourierFunction X(WaveFunction::saw(a, b, c, 44100, 16, false));
    //        return  FrequencyModulation::vibrato(WaveFunction::tri(a, b, c, 44100, 16), b, 5.0, 2.0);
    //        //return KarplusStrong::synthesis(a, b / 2.0, c, 44100, 16, KarplusStrong::decayMoveAverage, 4);
    //        //return FrequencyModulation::vibrato(KarplusStrong::synthesis(a, b, c, 44100, 16, KarplusStrong::decayMoveAverage, 2), b, 5.0, 2.0);
    //        //return FrequencyModulation::vibrato(KarplusStrong::synthesis(a, b, c, 44100, 16, KarplusStrong::decayMoveAverage, 2), b, 5.0, 2.0);
    //    };

  

    //WaveFunction k = s.getWaveFunction(func);
    WaveFunction l = WaveFunction::tri(0.02, 880, 2.0, 44100, 16);
    l = l & FrequencyModulation::bending(WaveFunction::tri(0.02, A5, 2.0, 44100, 16), A5, 0.5, B5 - A5);

    //std::cout << "play" << std::endl;
    l.playWave();
    //k.exportWave("cannon");
   
    //MorletFunction Y(k, G3, D5, pow(2.0, 1.0 / 12.0), 0.1);
    //std::cout << Y.exportWavelet("wavelettest") << std::endl;


    //WaveFunction S = FrequencyModulation::vibrato(WaveFunction::sin(0.02, 100, 5, 44100, 16), 100, 0.5, 0.2);
    //S = S & WaveFunction::sin(0.02, 100, 5, 44100, 16);
    //FourierFunction F(S);
    //MorletFunction G(S, 99, 101, 0.01, 1.0);
    //G.exportWaveletSpectrum("test2");

    //FourierFunction X(A);
    //MorletFunction Y(X, A3, A5, pow(2.0, 1.0 / 12.0), 1.0);
    //Y.exportWaveletSpectrum("KS-TEST");

    return 0;
}
