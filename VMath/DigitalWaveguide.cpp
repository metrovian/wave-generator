#include "DigitalWaveguide.h"
#include "Predefined.h"

DelayData DigitalWaveguide::calcRandomDelayLine(double _namp, double _freq)
{
    double ramp = _namp * pow(2.0, (double)header.BIT_PER_SAMPLE - 1.0);
    unsigned long long size = (unsigned long long)((double)header.SAMPLE_RATE / _freq);

    if (size > 0)
    {   
        std::queue<short> ret;
        for (unsigned long long i = 0; i < size; ++i)
        {
            ret.push((short)(ramp * (1.0 - 2.0 * (double)rand() / (double)RAND_MAX)));
        }

        return ret;
    }

    else
    {
        return std::queue<short>();
    }
}

short DigitalWaveguide::passSimpleLPF(const DelayData& _data, unsigned char _pow) const
{
    assert(_data.size() > _pow);

    DelayData temp = _data;
    long long sum = 0;

    for (unsigned char i = 0; i < _pow; ++i)
    {
        sum += temp.front();
        temp.pop();
    }

    return (short)((double)sum / (double)_pow);
}

short DigitalWaveguide::passDynamicLPF(const DelayData& _data, double _freq) const
{
    static double buf = 0;

    double coe = std::exp(-PI * _freq/ (double)header.SAMPLE_RATE);
    double ret = (1.0 - coe) * (double)_data.front() + coe * buf;

    buf = ret;

    return (short)ret;
}

short DigitalWaveguide::passPickDirectionLPF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0 && _pick <= 0.9);

    static double buf = 0;
    double ret = (1.0 - _pick) * (double)_data.front() + _pick * buf;

    buf = ret;

    return (short)ret;
}

short DigitalWaveguide::passPickPositionCF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0 && _pick <= 1.0);

    DelayData temp = _data;
    unsigned long long delay = (unsigned long long)ceil(_pick * (double)temp.size() + 0.5);

    for (unsigned long long i = 0; i < delay; ++i)
    {
        temp.pop();
    }

    return _data.front() - temp.front();
}
