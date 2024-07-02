#include "BowStringLP.h"

bool BowStringLP::synthesis(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    WaveData dat(calcWaveDataSize(_dura, _srate));
    DelayData train = calcBandLimDelayLine(_namp, _freq, band);

    if (train.size() > 0)
    {
        DelayData proc1 = passPickPositionCF(train, pos);

    }

    setWaveData(dat);
    return true;
}
