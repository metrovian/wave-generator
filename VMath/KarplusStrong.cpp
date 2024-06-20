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

WaveFunction KarplusStrong::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, WaveData(*_decay)(WaveData, unsigned long long, double), double _drate)
{
    unsigned long long size = (unsigned long long)(_dura * (double)_srate);

    WaveFunction ret;
    WaveData dat(size);

    if (_freq > 0)
    {
        WaveData noise = getNoiseBurst(_namp, _freq, _srate, _sbit).getWaveData();
        WaveData origin = noise;

        dat = _decay(noise, size, _drate);
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveData KarplusStrong::decayMoveAverage(WaveData _noise, unsigned long long _size, double _drate)
{
    WaveData ret(_size);

    for (unsigned long long i = 0; i < _size; ++i)
    {
        ret[i] = _noise[i % _noise.size()];

        short avg = 0;
        for (unsigned long long j = 0; i < (unsigned long long)_drate; ++j)
        {
            avg += _noise[(i + j) % _noise.size()];
        }

        _noise[i % _noise.size()] = short(avg / (double)_drate);
    }

    return ret;
}

WaveData KarplusStrong::decayTimeFractional(WaveData _noise, unsigned long long _size, double _drate)
{
    WaveData ret(_size);
    WaveData origin = _noise;

    for (unsigned long long i = 0; i < _size; ++i)
    {
        ret[i] = _noise[i % _noise.size()];
        _noise[i % _noise.size()] = origin[i % _noise.size()] / _drate;
    }

    return ret;
}

WaveData KarplusStrong::decayTimeExponential(WaveData _noise, unsigned long long _size, double _drate)
{
    WaveData ret(_size);
    WaveData origin = _noise;

    for (unsigned long long i = 0; i < _size; ++i)
    {
        ret[i] = _noise[i % _noise.size()];
        _noise[i % _noise.size()] = (short)((double)origin[i % _noise.size()] * std::exp(-std::pow(10.0, _drate) * (double)i));
    }

    return ret;
}
