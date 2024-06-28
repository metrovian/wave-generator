#include "PluckStringKS.h"

bool PluckStringKS::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    DelayData rand = getRandomDelayLine(_namp, _freq);
    WaveData dat(calcWaveDataSize(_dura, _srate));

    for (unsigned long long i = 0; i < dat.size(); ++i)
    {
        dat[i] = rand.front();

        rand.push(passSimpleLPF(rand, 2));
        rand.pop();
    }

    setWaveData(dat);

    return false;
}
