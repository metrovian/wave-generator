#include "WaveFunction.h"
#include "Predefined.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() 
{
    std::vector<WaveFunction> over;
    std::vector<int> time;
    int unit = 500;

    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, C5, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, B4, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, G4, 1.0, 44100, 16, true)); time.push_back(unit/2.0);
    over.push_back(WaveFunction::saw(0.02, A4, 1.0, 44100, 16, true)); time.push_back(unit/2.0);
    over.push_back(WaveFunction::saw(0.02, B4, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, C5, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, A4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, G4, 1.0, 44100, 16, true)); time.push_back(unit * 4);
    over.push_back(WaveFunction::saw(0.02, A3, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, F4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, F4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, B3, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 4);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, C5, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, B4, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, G4, 1.0, 44100, 16, true)); time.push_back(unit / 2.0);
    over.push_back(WaveFunction::saw(0.02, A4, 1.0, 44100, 16, true)); time.push_back(unit / 2.0);
    over.push_back(WaveFunction::saw(0.02, B4, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, C5, 1.0, 44100, 16, true)); time.push_back(unit);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, A4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, G4, 1.0, 44100, 16, true)); time.push_back(unit * 4);
    over.push_back(WaveFunction::saw(0.02, A3, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, F4, 1.0, 44100, 16, true)); time.push_back(unit * 2);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, F4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, B3, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 0.5);
    over.push_back(WaveFunction::saw(0.02, D4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, E4, 1.0, 44100, 16, true)); time.push_back(unit * 1);
    over.push_back(WaveFunction::saw(0.02, C4, 1.0, 44100, 16, true)); time.push_back(unit * 4);


    char fname[256]{};
    
    for (int i = 0; i < over.size(); i++)
    {
        sprintf_s(fname, "..\\TEST\\%d.wav", i);
        over[i].exportWave(fname);
    }

    for (int i = 0; i < over.size(); i++)
    {
        sprintf_s(fname, "..\\TEST\\%d.wav", i);
        PlaySoundA(fname, 0, SND_FILENAME | SND_ASYNC);
        Sleep(time[i]);
    }

    return 0;
}
