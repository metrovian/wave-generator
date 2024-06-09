#include "WaveFunction.h"
#include "MelodyFunction.h"
#include "Predefined.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() 
{
    MelodyFunction s = MelodyFunction::somewhere_over_the_rainbow(120);
    WaveFunction k = s.getWaveFunction(44100, 16, [](double a, double b, double c, unsigned short d, unsigned short e)
    {
        return WaveFunction::sqr(a, b, c, d, e, 0.2);
    });
    
    k.playWave();
   
    return 0;
}
