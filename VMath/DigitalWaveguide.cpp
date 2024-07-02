#include "DigitalWaveguide.h"
#include "Predefined.h"

WaveData DigitalWaveguide::extractFrontData(const DelayData& _data) const
{
    return extractFrontData(_data, _data.size());
}

WaveData DigitalWaveguide::extractFrontData(const DelayData& _data, unsigned long long _count) const
{
    WaveData ret;
    DelayData temp = _data;

    for (unsigned long long i = 0; i < _count; ++i)
    {
        ret.push_back(temp.front());
        temp.pop();
    }

    return ret;
}

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

DelayData DigitalWaveguide::calcBandLimDelayLine(double _namp, double _freq, unsigned char _band)
{
    if (_freq > 0)
    {
        double ramp = _namp * pow(2.0, (double)header.BIT_PER_SAMPLE - 1.0);
        double dt = 1.0 / (double)header.SAMPLE_RATE;
        unsigned long long size = (unsigned long long)((double)header.SAMPLE_RATE / _freq);

        if (size > 0)
        {
            std::queue<short> ret;
            for (unsigned long long i = 0; i < size; ++i)
            {
                double sum = 0;
                for (unsigned long long j = 1; j < (unsigned long long)_band; ++j)
                {
                    sum += cos(2.0 * PI * _freq * dt * (double)i * (double)j);
                }

                ret.push((short)(ramp * sum / (double)_band));
            }

            return ret;
        }
    }

    return std::queue<short>();
}

short DigitalWaveguide::passSimpleLPF(const DelayData& _data, unsigned char _pow) const
{
    assert(_data.size() > _pow);

    WaveData ext = extractFrontData(_data, (unsigned long long)_pow);
    long long sum = 0;

    for (unsigned long long i = 0; i < ext.size(); ++i)
    {
        sum += ext[i];
    }

    return (short)((double)sum / (double)_pow);
}

short DigitalWaveguide::passDynamicLPF(const DelayData& _data, short _prev, double _freq) const
{
    assert(_level >= 0.0 && _level <= 1.0);

    double ome = PI * _freq / (double)header.SAMPLE_RATE;
    double coe = (1.0 - ome) / (1.0 + ome);
    double ret = (1.0 - coe) * (double)_data.front() + coe * (double)_prev;

    return (short)ret;
}

short DigitalWaveguide::passStringDF(const DelayData& _data, double _damp) const
{
    assert(_damp >= 0.0 && _damp <= 1.0);

    WaveData ext = extractFrontData(_data, 2);
    double sum = (1.0 - _damp) * (double)ext[0] + _damp * (double)ext[1];

    return (short)sum;
}

short DigitalWaveguide::passStringAPF(const DelayData& _data, short _prev, double _damp) const
{
    assert(_damp >= -1.0 && _damp <= 1.0);

    WaveData ext = extractFrontData(_data, 2);
    double sum = _damp * (double)ext[0] + (double)ext[1] - _damp * (double)_prev;

    return (short)sum;
}

DelayData DigitalWaveguide::passPickDirectionLPF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0.0 && _pick <= 1.0);

    DelayData ret;
    WaveData ext = extractFrontData(_data);

    double res = 0;

    for (unsigned long long i = 0; i < _data.size(); ++i)
    {
        res = (1.0 - _pick) * (double)ext[i] + _pick * res;
        ret.push(res);
    }

    return ret;
}

DelayData DigitalWaveguide::passPickPositionCF(const DelayData& _data, double _pick) const
{
    assert(_pick >= 0.0 && _pick <= 1.0);

    DelayData ret;
    WaveData ext = extractFrontData(_data);

    unsigned long long delay = (unsigned long long)ceil(_pick * (double)_data.size());

    for (unsigned long long i = 0; i < _data.size(); ++i)
    {
        if (i >= delay) 
        {
            ret.push(ext[i] - ext[i - delay]);
        }

        else
        {
            ret.push(ext[i]);
        }
    }

    return ret;
}

WaveFunction DigitalWaveguide::castWaveFunction()
{
    return *(dynamic_cast<WaveFunction*>(this));
}
