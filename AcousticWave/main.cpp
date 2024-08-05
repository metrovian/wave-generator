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
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



int main() 
{
    PipeFDTD x(10.0, 0.5, 120, 4410000);
    WaveFunction y = x.castWaveFunction(1.0, 0.8, 44100, 16);
    y.playWave();

    return 0;

    //BowStringLP Y3(0.80, G4, 1.0, 44100, 16);
    //FrequencyModulation::vibrato(Y3.castWaveFunction(), G4, 5.0, 0.7).playWave();

    return 0;
}
