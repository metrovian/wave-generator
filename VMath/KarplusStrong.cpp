#include "KarplusStrong.h"

WaveFunction KarplusStrong::getNoiseBurst(double _namp, double _freq, unsigned short _srate, unsigned short _sbit)
{
    WaveFunction ret;
    WaveData dat;

    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);
    unsigned long long size = (unsigned long long)((double)_srate / _freq);

    for (unsigned long long i = 0; i < size; ++i)
    {
        dat.push_back((short)(ramp * (1.0 - 2.0 * (double)rand() / (double)RAND_MAX)));
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveFunction KarplusStrong::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, short(*_decay)(WaveData, unsigned long long, unsigned long long, double), double _drate)
{
    unsigned long long size = (unsigned long long)(_dura * (double)_srate);

    WaveFunction ret;
    WaveData dat(size);

    if (_freq > 0)
    {
        WaveData noise = getNoiseBurst(_namp, _freq, _srate, _sbit).getWaveData();
        WaveData origin = noise;

        for (unsigned long long i = 0; i < size; ++i)
        {
            dat[i] = noise[i % noise.size()];
            noise[i % noise.size()] = _decay(noise, i, noise.size(), _drate);
        }
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

short KarplusStrong::decayMoveAverage(WaveData _data, unsigned long long _idx, unsigned long long _unit, double _drate)
{
    short ret = 0;

    for (unsigned long long i = 0; i < (unsigned long long)_drate; ++i)
    {
        ret += _data[(_idx + i) % _unit];
    }

    return (short)((double)ret / _drate);
}

short KarplusStrong::decayTimeExponential(WaveData _data, unsigned long long _idx, unsigned long long _unit, double _drate)
{
    return _data[_idx % _unit] / _drate;
}
