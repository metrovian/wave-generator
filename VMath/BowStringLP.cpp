#include "BowStringLP.h"

BowStringLP::BowStringLP(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    synthesis(_namp, _freq, _dura, _srate, _sbit);
}

bool BowStringLP::synthesis(double _namp, double _freq, double _dura, unsigned int _srate, unsigned short _sbit)
{
    setWaveHeader(_srate, _sbit);

    WaveData dat(calcWaveDataSize(_dura, _srate));
    DelayData train = calcBandLimDelayLine(_namp, _freq, band);

    if (train.size() > 0)
    {
        DelayData raw1 = passStringElasticModulusLPF(train, modulus);
        DelayData raw2 = passStringPositionCF(raw1, pos);
        DelayData proc1 = raw2;
        DelayData proc2 = proc1;
        
        dat[0] = 0;
        for (unsigned long long i = 1; i < dat.size(); ++i)
        {
            dat[i] = passDynamicLPF(proc2, dat[i - 1], _freq);

            double dcy = 0.0;
            if ((double)i < (double)dat.size() * start)
            {
                dcy = 0.01 + ((double)i / (double)dat.size()) * decay / start;
            }

            else if ((double)i < (double)dat.size() * end)
            {
                dcy = 0.01 + decay;
            }

            else
            {
                dcy = 0.01 + (1.0 - (double)i / (double)dat.size()) * decay;
            }

            raw2.push(raw2.front());
            proc1.push(passStringDF(raw2, _freq, 0.0, dcy));
            proc2.push(passStringDF(proc1, _freq, 0.5, decay));

            raw2.pop();
            proc1.pop();
            proc2.pop();
        }

        //setWaveData(dat);
        setWaveData(passAutoRegressionLPC(dat, num));
    }

    else
    {
        setWaveData(dat);
    }

    return true;
}
