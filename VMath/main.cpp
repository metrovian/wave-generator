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
#include "BowStringLP.h"
#include "HammerStringCM.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



int main() 
{
    //BowStringLP Y(0.80, G1, 1.0, 44100, 16);
    //Y.playWave();

    //BowStringLP Y2(0.80, D2, 1.0, 44100, 16);
    //Y2.playWave();

    HammerStringCM Z(0.80, G3, 1.0, 44100, 16);
    Z.playWave();

    PluckStringKS X(0.80, G3, 1.0, 44100, 16);
    X.playWave();

    //BowStringLP Y3(0.80, G4, 1.0, 44100, 16);
    //FrequencyModulation::vibrato(Y3.castWaveFunction(), G4, 5.0, 0.7).playWave();

    //auto func = [](double a, double b, double c)
    //    {
    //        BowStringLP Y(a, b, c, 44100, 16);
    //        return FrequencyModulation::vibrato(Y.castWaveFunction(), b, 5.0, 0.7);
    //        //PluckStringEKS s(a, b * pow(2.0, 3.0/12.0) / 2.0, c, 44100, 16);
    //        //WaveFunction* k = dynamic_cast<WaveFunction*>(&s);
    //        ////return WaveFunction::saw(0.02, a, b, 44100, 16, false);
    //        //return *k;
    //        //return KarplusStrong::synthesis(0.02, a, b, 44100, 16, KarplusStrong::decayMoveAverage, 2);
    //    };
    //auto func2 = [](double a, double b)
    //    {
    //        PluckStringEKS s(0.8, a, b, 44100, 16);
    //        return s.castWaveFunction();
    //        //return KarplusStrong::synthesis(0.02, a, b, 44100, 16, KarplusStrong::decayMoveAverage, 2);
    //    };
    //MIDI dev;
    //dev.setSound(func2, 5);
    //dev.open(0);
    ////dev.setVampFunction(MIDI::vampLinear());
    //dev.start();
    //
    //getchar();
    //dev.stop();
    //dev.close();

    //PluckStringEKS X(0.2, E5, 5.0, 44100, 16);
    //X.playWave();


    //PluckStringEKS X5(0.80, E5, 5.5, 44100, 16, 15.0, 0.3, 0.1, 0.9, 0.1);
    //PluckStringEKS Xs5(0.80, E5, 5.5, 44100, 16, 15.0, 0.3, 0.1, 0.1, 0.1);


    //X5.playWave();
    //Xs5.playWave();

    //X.playWave();
    //Xs.playWave();
    //X.playWave();
    //Xs.playWave();
    //X.playWave();
    //Xs.playWave();
    //X.playWave();
    //Xs.playWave();

    //BowStringLP Y(0.80, C2, 2.0, 44100, 16);
    //Y.playWave();

    //WaveFunction::sqr(0.80, G2, 2.0, 44100, 16, 0.2).playWave();
    //FourierFunction Z(Y.castWaveFunction());
    //Z.exportWaveSpectrum("NORM");
    //Y.exportWave("NORMAL");
    //WaveFunction test = WaveFunction::sqr(0.02, 2000, 5.0, 44100, 16, 0.3);
    //FourierFunction ok(test);

    //ok.exportWaveSpectrum("spectrumtest");
    //ok.playWave();

    //ok.setLPF(3000, -3);
    //ok.playWave();


    //PluckStringEKS s(0.8, G4 * pow(2.0, 3.0/12.0) / 2.0, 5.0, 44100, 16);
    //PluckStringEKS s1(0.8, E2, 3.0, 44100, 16);
    //PluckStringKS s1k(0.8, E2, 3.0, 44100, 16);

    //PluckStringEKS s2(0.8, A2, 3.0, 44100, 16);
    //PluckStringKS s2k(0.8, A2, 3.0, 44100, 16);

    //PluckStringEKS s3(0.8, D3, 3.0, 44100, 16);
    //PluckStringKS s3k(0.8, D3, 3.0, 44100, 16);

    //PluckStringEKS s4(0.8, G3, 3.0, 44100, 16);
    //PluckStringKS s4k(0.8, G3, 3.0, 44100, 16);

    //PluckStringEKS s5(0.8, B3, 3.0, 44100, 16);
    //PluckStringKS s5k(0.8, B3, 3.0, 44100, 16);

    //PluckStringEKS s6(0.8, E4, 3.0, 44100, 16);
    //PluckStringKS s6k(0.8, E4, 3.0, 44100, 16);


    //s1.playWave();
    //s1k.playWave();

    //s2.playWave();
    //s2k.playWave();

    //s3.playWave();
    //s3k.playWave();

    //s4.playWave();
    //s4k.playWave();

    //s5.playWave();
    //s5k.playWave();

    //s6.playWave();
    //s6k.playWave();


    //MelodyFunction s = MelodyFunction::over_the_rainbow(80);
    //WaveFunction l1 = s.getWaveFunction(func);

    //l1.playWave();
    //(l1).exportWave("C:\\Users\\lovel\\Desktop\\cannon_newks_mod");


    
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
