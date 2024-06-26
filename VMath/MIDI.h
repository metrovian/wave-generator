#pragma once
#include "WaveFunction.h"

#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <thread>

class MIDI
{
protected: /* data */
    WaveFunction sound[88];
    std::vector<double> vamps = vampConstant();

private: /* control */
    bool sustain = false;

private: /* handle */
    HMIDIIN midi;
    static void CALLBACK inputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

public: /* public use */
	bool open(unsigned int _id);
    bool start();
    bool stop();
    bool close();

    bool setSound(WaveFunction(*_wave)(double _freq, double _dura), double _fdura);
    bool setVampFunction(std::vector<double> _vamps);

    static std::vector<double> vampConstant();
    static std::vector<double> vampLinear();
};