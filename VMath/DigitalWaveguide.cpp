#include "DigitalWaveguide.h"
#include "Predefined.h"

DelayData DigitalWaveguide::calcRandomDelayLine(double _namp, double _freq)
{
    if (_freq > 0)
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
    }

    return std::queue<short>();
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

short DigitalWaveguide::passDynamicLPF(const DelayData& _data, short _prev, double _freq) const
{
    double coe = std::exp(-PI * _freq/ (double)header.SAMPLE_RATE);
    double ret = (1.0 - coe) * (double)_data.front() + coe * (double)_prev;

    return (short)ret;
}

short DigitalWaveguide::passStringDF(const DelayData& _data, double _damp) const
{
    assert(_damp >= 0.0 && _damp <= 1.0);

    DelayData temp = _data;
    double sum = (1.0 - _damp) * (double)temp.front();

    temp.pop();
    sum += _damp * (double)temp.front();

    return (short)sum;
}

short DigitalWaveguide::passStringAPF(const DelayData& _data, short _prev, double _damp) const
{
    assert(_damp >= -1.0 && _damp <= 1.0);

    DelayData temp = _data;
    double sum = _damp * (double)temp.front();

    temp.pop();
    sum += (double)temp.front();
    sum -= _damp * (double)_prev;

    return (short)sum;
}

DelayData DigitalWaveguide::passPickDirectionLPF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0.0 && _pick <= 0.9);

    DelayData ret;
    DelayData temp = _data;

    double buf = 0;
    double res = 0;

    for (unsigned long long i = 0; i < _data.size(); ++i)
    {
        res = (1.0 - _pick) * (double)temp.front() + _pick * buf;

        ret.push(res);
        temp.pop();

        buf = res;
    }

    return ret;
}

DelayData DigitalWaveguide::passPickPositionCF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0.0 && _pick <= 1.0);

    DelayData ret;
    DelayData demp = _data;
    DelayData temp = _data;

    unsigned long long delay = (unsigned long long)ceil(_pick * (double)temp.size() + 0.5);

    for (unsigned long long i = 0; i < delay; ++i)
    {
        demp.push(0);
        demp.pop();
    }

    for (unsigned long long i = 0; i < _data.size(); ++i)
    {
        ret.push(temp.front() - demp.front());

        demp.pop();
        temp.pop();
    }

    return ret;
}
