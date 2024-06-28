#include "DigitalWaveguide.h"

DelayData DigitalWaveguide::getRandomDelayLine(double _namp, double _freq)
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
