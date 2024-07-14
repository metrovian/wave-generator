#include "HammerStringCM.h"

HammerStringCM::HammerStringCM(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool HammerStringCM::synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    DelayData rand1 = calcImpulseDelayLine(_namp, _freq, 0.25, 0.26);
    DelayData rand2 = calcImpulseDelayLine(_namp, _freq, 0.27, 0.28);
    DelayData rand3 = calcImpulseDelayLine(_namp, _freq, 0.29, 0.30);

    unsigned long long size = rand1.size();

    DelayData rand;
    for (unsigned long long i = 0; i < size; ++i)
    {
        rand.push(rand1.front() + 0.9 * rand2.front() + 0.6 * rand3.front());

        rand1.pop();
        rand2.pop();
        rand3.pop();
    }

    WaveData dat(calcWaveDataSize(_dura, _srate));

    if (rand.size() > 0)
    {
        for (unsigned long long i = 0; i < dat.size(); ++i)
        {
            dat[i] = rand.front();

            rand.push(passSimpleLPF(rand, 2));
            rand.pop();
        }
    }

    setWaveData(dat);
    return true;
}
