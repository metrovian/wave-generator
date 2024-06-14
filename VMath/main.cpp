#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "FourierTransform.h"
#include "Predefined.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() 
{
    WaveFunction test = WaveFunction::sqr(0.02, 2000, 5.0, 44100, 16, 0.3);
    FourierFunction ok(test);

    ok.exportWaveSpectrum("spectrumtest");
    ok.playWave();

    ok.setLPF(3000, -3);
    ok.playWave();

    //MelodyFunction s = MelodyFunction::over_the_rainbow(120);
    //WaveFunction k = s.getWaveFunction(44100, 16, [](double a, double b, double c, unsigned short d, unsigned short e)
    //{
    //    return WaveFunction::sin(a, b* pow(2.0, 7.0 / 12.0), c, d, e);
    //    //return WaveFunction::sqr(a, b, c, d, e, 0.2);
    //});
    //
    //k.playWave();
   
    return 0;
}
