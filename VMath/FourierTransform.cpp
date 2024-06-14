#include "FourierTransform.h"
#include "Predefined.h"

FourierFunction::FourierFunction(const WaveFunction& _wave)
{
    wdata = _wave.getWaveData();
    header = _wave.getWaveHeader();
    fft();
}

bool FourierFunction::fft()
{
    unsigned long long wsize = wdata.size();
    unsigned long long tsize = 2;
    unsigned long long power = 1;

    if (wsize < 2) return false;
    
    while (tsize < wsize)
    {
        tsize <<= 1;
        ++power;
    }
    
    FourierData convert;
    for (unsigned long long i = 0; i < tsize; ++i)
    {
        if (i < wsize)
        {
            convert.push_back(std::complex<double>(wdata[i], 0));
        }
        
        else
        {
            convert.push_back(std::complex<double>(0, 0));
        }
    }

    for (unsigned long long i = 0; i < tsize; ++i)
    {
        unsigned long long rev = 0;
        for (unsigned long long j = 0; j < power; ++j)
        {
            rev = (rev << 1) | ((i >> j) & 1);
        }
        if (i < rev)
        {
            std::swap(convert[i], convert[rev]);
        }
    }

    for (unsigned long long s = 1; s <= power; ++s)
    {
        unsigned long long m = static_cast<unsigned long long>(1) << s;
        std::complex<double> wm = std::exp(std::complex<double>(0, -2.0 * PI / (double)m));

        for (unsigned long long k = 0; k < tsize; k += m)
        {
            std::complex<double> w = 1;
            for (unsigned long long j = 0; j < m / 2; ++j)
            {
                std::complex<double> t = w * convert[k + j + m / 2];
                std::complex<double> u = convert[k + j];
                convert[k + j] = u + t;
                convert[k + j + m / 2] = u - t;
                w *= wm;
            }
        }
    }

    fdata = convert;

    std::ofstream output("test.csv");


    for(auto& pt : fdata)
    {
        output << sqrt(pt.real() * pt.real() + pt.imag() * pt.imag()) << std::endl;
    }

    output.close();

    return true;
}

bool FourierFunction::ifft()
{
    unsigned long long fsize = fdata.size();
    unsigned long long tsize = 2;
    unsigned long long power = 1;

    if (fsize < 2) return false;

    while (tsize < fsize)
    {
        tsize <<= 1;
        ++power;
    }

    FourierData convert;
    for (unsigned long long i = 0; i < tsize; ++i)
    {
        if (i < fsize)
        {
            convert.push_back(fdata[i]);
        }

        else
        {
            convert.push_back(std::complex<double>(0, 0));
        }
    }

    for (unsigned long long i = 0; i < tsize; ++i)
    {
        unsigned long long rev = 0;
        for (unsigned long long j = 0; j < power; ++j)
        {
            rev = (rev << 1) | ((i >> j) & 1);
        }
        if (i < rev)
        {
            std::swap(convert[i], convert[rev]);
        }
    }

    for (unsigned long long s = 1; s <= power; ++s)
    {
        unsigned long long m = static_cast<unsigned long long>(1) << s;
        std::complex<double> wm = std::exp(std::complex<double>(0, 2.0 * PI / (double)m));

        for (unsigned long long k = 0; k < tsize; k += m)
        {
            std::complex<double> w = 1;
            for (unsigned long long j = 0; j < m / 2; ++j)
            {
                std::complex<double> t = w * convert[k + j + m / 2];
                std::complex<double> u = convert[k + j];
                convert[k + j] = u + t;
                convert[k + j + m / 2] = u - t;
                w *= wm;
            }
        }
    }

    WaveData ret;
    for (const auto& pt : convert)
    {
        ret.push_back((unsigned long long)(pt.real() / (double)tsize));
    }

    wdata = ret;
    setWaveHeader(header.SAMPLE_RATE, header.BIT_PER_SAMPLE);

    return true;
}

double FourierFunction::getFrequency(unsigned long long _idx) const
{
    return (double)_idx * (double)header.SAMPLE_RATE / (double)fdata.size();
}

bool FourierFunction::setLPF(double _freq, double _brate)
{
    if (_brate > 0) return false;

    for (unsigned long long i = 0; i < fdata.size() / 2; i++)
    {
        if (getFrequency(i) > _freq)
        {
            fdata[i] *= pow(10.0, _brate);
            fdata[fdata.size() - i - 1] *= pow(10, _brate);
        }
    }

    bool cond1 = ifft();
    bool cond2 = fft();

    return cond1 && cond2;
}

bool FourierFunction::setHPF(double _freq, double _brate)
{
    if (_brate > 0) return false;

    for (unsigned long long i = 0; i < fdata.size() / 2; i++)
    {
        if (getFrequency(i) < _freq)
        {
            fdata[i] *= pow(10.0, _brate);
            fdata[fdata.size() - i - 1] *= pow(10, _brate);
        }
    }

    bool cond1 = ifft();
    bool cond2 = fft();

    return cond1 && cond2;
}

bool FourierFunction::setBPF(double _freq1, double _freq2, double _brate)
{
    if (_brate > 0) return false;

    for (unsigned long long i = 0; i < fdata.size() / 2; i++)
    {
        double freq = getFrequency(i);
        if ((_freq1 < freq) && (freq < _freq2))
        {
            fdata[i] *= pow(10.0, _brate);
            fdata[fdata.size() - i - 1] *= pow(10, _brate);
        }
    }

    bool cond1 = ifft();
    bool cond2 = fft();

    return cond1 && cond2;
}

bool FourierFunction::exportWaveSpectrum(const std::string& _fname) const
{
    std::ofstream file(_fname + ".csv");

    if (!file)
    {
        return false;
    }

    for (unsigned long long i = 0; i < fdata.size() / 2; ++i)
    {
        file << (double)i * (double)header.SAMPLE_RATE / (double)fdata.size() << ", " << std::norm(fdata[i]) << std::endl;
    }

    return true;
}

