#include "HammerStringCM.h"

HammerStringCM::HammerStringCM(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool HammerStringCM::synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    DelayData rand1 = calcImpulseDelayLine(_namp, _freq, 0.20, 0.29);
    DelayData rand2 = calcImpulseDelayLine(_namp, _freq, 0.60, 0.65);
    DelayData rand3 = calcImpulseDelayLine(_namp, _freq, 0.80, 0.82);

    rand1 = passStringElasticModulusLPF(rand1, 0.050);
    rand2 = passStringElasticModulusLPF(rand2, 0.010);
    rand3 = passStringElasticModulusLPF(rand3, 0.010);

    unsigned long long size = rand1.size();

    DelayData rand;
    for (unsigned long long i = 0; i < size; ++i)
    {
        rand.push(rand1.front());

        rand1.pop();
        rand2.pop();
        rand3.pop();
    }

    WaveData dat(calcWaveDataSize(_dura, _srate));

    if (rand.size() > 0)
    {
        dat[0] = passDynamicLPF(rand, 0, _freq);

        rand.push(passStringDF(rand, _freq, 0.9, 10.0));
        rand.pop();

        for (unsigned long long i = 1; i < dat.size(); ++i)
        {
            dat[i] = passDynamicLPF(rand, dat[i-1], _freq);

            rand.push(passStringDF(rand, _freq, 0.5, 10.0));
            rand.pop();
        }
    }

    setWaveData(dat);
    return true;
}
