#include "FourierTransform.h"
#include "Predefined.h"

FourierFunction::FourierFunction(const WaveFunction& _wave)
{
    wdata = _wave.getWaveData();
    header = _wave.getWaveHeader();
}
FourierFunction::FourierFunction(const FourierData& _data, unsigned short _srate, unsigned short _sbit)
{
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

    return true;
}

