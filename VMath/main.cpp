#pragma once
#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"
#include "WaveletTransform.h"
#include "FrequencyModulation.h"
#include "AmplitudeModulation.h"
#include "MIDI.h"
#include "DigitalWaveguide.h"
#include "PluckStringKS.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



int main() 
{

    auto func = [](double a, double b)
        {
            PluckStringEKS s(0.02, a, b, 44100, 16);
            WaveFunction* k = dynamic_cast<WaveFunction*>(&s);
            //return WaveFunction::saw(0.02, a, b, 44100, 16, false);
            return *k;
            //return KarplusStrong::synthesis(0.02, a, b, 44100, 16, KarplusStrong::decayMoveAverage, 2);
        };

    MIDI dev;
    dev.setSound(func, 5);
    dev.open(0);
    //dev.setVampFunction(MIDI::vampLinear());
    dev.start();
    
    getchar();
    dev.stop();
    dev.close();

    //PluckStringEKS X(0.02, A4, 2.0, 44100, 16);
    //X.playWave();

    //PluckStringKS Y(0.02, A4, 2.0, 44100, 16);
    //Y.playWave();
    //WaveFunction test = WaveFunction::sqr(0.02, 2000, 5.0, 44100, 16, 0.3);
    //FourierFunction ok(test);

    //ok.exportWaveSpectrum("spectrumtest");
    //ok.playWave();

    //ok.setLPF(3000, -3);
    //ok.playWave();

    ////MelodyFunction s = MelodyFunction::cannon(240);
    //MelodyFunction s = MelodyFunction::over_the_rainbow(150);
    //std::cout << "calculating" << std::endl;

    
    //auto func = [](double a, double b, double c)
    //    {
    //        //FourierFunction X(WaveFunction::saw(a, b, c, 44100, 16, false));
    //        return  FrequencyModulation::vibrato(WaveFunction::tri(a, b, c, 44100, 16), b, 5.0, 2.0);
    //        //return KarplusStrong::synthesis(a, b / 2.0, c, 44100, 16, KarplusStrong::decayMoveAverage, 4);
    //        //return FrequencyModulation::vibrato(KarplusStrong::synthesis(a, b, c, 44100, 16, KarplusStrong::decayMoveAverage, 2), b, 5.0, 2.0);
    //        //return FrequencyModulation::vibrato(KarplusStrong::synthesis(a, b, c, 44100, 16, KarplusStrong::decayMoveAverage, 2), b, 5.0, 2.0);
    //    };

  

    //WaveFunction k = s.getWaveFunction(func);
    //WaveFunction l = AmplitudeModulation::envelopeADS(WaveFunction::tri(0.02, 880, 3.0, 44100, 16), 1.0, 1.0, 1.0);
    //l = l & WaveFunction::tri(0.02, 880, 3.0, 44100, 16);
    //l = l & FrequencyModulation::bending(WaveFunction::tri(0.02, A5, 1.0, 44100, 16), A5, G5, 1.0);
    //l = l & FrequencyModulation::vibrato(WaveFunction::tri(0.02, G5, 2.0, 44100, 16), G5, 7.0, 4.0);

    //std::cout << "play" << std::endl;
    //l.playWave();
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
