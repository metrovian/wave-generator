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
#include "StringFDTD.h"
#include "PipeFDTD.h"
#include "HornFDTD.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



int main() 
{
    HornFDTD xa(480.0, 0.9, 441000);
    WaveFunction ya = xa.castWaveFunction(0.1, 0.2, 44100, 16);
    ya.playWave();

    PipeFDTD x(480.0, 0.9, 441000);
    WaveFunction y = x.castWaveFunction(0.1, 0.8, 44100, 16);
    y.playWave();

    StringFDTD z(0.2, 0.9, 441000, 150, 0.0072);
    WaveFunction g = z.castWaveFunction(0.1, 0.8, 44100, 16);
    g.playWave();

    return 0;

    //BowStringLP Y3(0.80, G4, 1.0, 44100, 16);
    //FrequencyModulation::vibrato(Y3.castWaveFunction(), G4, 5.0, 0.7).playWave();

    return 0;
}
