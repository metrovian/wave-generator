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

PluckStringEKS::PluckStringEKS(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, double _damp, double _tune, double _dir, double _pos, double _low)
{
    damp = _damp;
    tune = _tune;
    dir = _dir;
    pos = _pos;
    low = _low;

    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool PluckStringEKS::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    WaveData dat(calcWaveDataSize(_dura, _srate));
    DelayData rand = calcRandomDelayLine(_namp, _freq);
    
    if (rand.size() > 0)
    {
        DelayData proc1 = passPickDirectionLPF(rand, dir);
        DelayData proc2 = passPickPositionCF(proc1, pos);
        DelayData proc3;

        DelayData proc2m1 = proc2; proc2m1.pop();

        double buf = 0;

        dat[0] = passDynamicLPF(proc2, 0, _freq * low);

        proc3.push(passStringDF(proc2, damp));
        proc3.push(passStringDF(proc2m1, damp));

        proc2.push(passStringAPF(proc3, buf, tune));
        proc2m1.push(passStringAPF(proc3, buf, tune));
        proc2m1.pop();

        buf = proc2.back();
        proc2.pop();

        for (unsigned long long i = 1; i < dat.size(); ++i)
        {
            dat[i] = passDynamicLPF(proc2, dat[i - 1], _freq * low);

            proc3.pop();
            proc3.push(passStringDF(proc2, damp));

            proc2.push(passStringAPF(proc3, buf, tune));
            proc2m1.push(passStringAPF(proc3, buf, tune));
            proc2m1.pop();

            buf = proc2.back();
            proc2.pop();
        }
    }

    setWaveData(dat);
    return true;
}
