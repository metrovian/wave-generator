#include "PluckStringKS.h"

PluckStringKS::PluckStringKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

PluckStringKS::PluckStringKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, unsigned char _pow)
{
    pow = _pow;
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool PluckStringKS::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    DelayData rand = calcRandomDelayLine(_namp, _freq);
    WaveData dat(calcWaveDataSize(_dura, _srate));

    for (unsigned long long i = 0; i < dat.size(); ++i)
    {
        dat[i] = rand.front();

        rand.push(passSimpleLPF(rand, pow));
        rand.pop();
    }

    setWaveData(dat);

    return true;
}

PluckStringEKS::PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool PluckStringEKS::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    DelayData rand = calcRandomDelayLine(_namp, _freq);
    DelayData proc1;
    DelayData proc2;

    for (unsigned long long i = 0; i < rand.size(); ++i)
    {
        proc1.push(passPickDirectionLPF(rand, dir));

        rand.push(0);
        rand.pop();
    }

    for (unsigned long long i = 0; i < proc1.size(); ++i)
    {
        proc2.push(passPickPositionCF(proc1, pos));

        proc1.push(0);
        proc1.pop();
    }

    WaveData dat(calcWaveDataSize(_dura, _srate));

    for (unsigned long long i = 0; i < dat.size(); ++i)
    {
        dat[i] = passDynamicLPF(proc2, _freq * freq);

        proc2.push(passSimpleLPF(proc2, pow));
        proc2.pop();
    }

    setWaveData(dat);
    return true;
}
