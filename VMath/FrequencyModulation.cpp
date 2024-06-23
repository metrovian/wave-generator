#include "FrequencyModulation.h"
#include "Predefined.h"

WaveFunction FrequencyModulation::vibrato(WaveFunction _wave, double _freq, double _vfreq, double _vdepth)
{
    WaveFunction ret;
    WaveHeader head = _wave.getWaveHeader();
    WaveData dat = _wave.getWaveData();

    std::vector<double> vibration(dat.size());
    std::vector<short> res(dat.size());

    double rate = 2.0 * PI * _vfreq;

    for (unsigned long long i = 0; i < vibration.size(); ++i)
    {
        vibration[i] = _vdepth / _freq / rate * cos(rate * (double)i / (double)head.SAMPLE_RATE);
        res[i] = dat[(unsigned long long)((double)i + (double)head.SAMPLE_RATE * (vibration[0] - vibration[i])) % dat.size()];
    }

    ret.setWaveFunction(res, head);

    return ret;
}
