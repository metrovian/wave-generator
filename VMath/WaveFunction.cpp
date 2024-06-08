#include "WaveFunction.h"
#include "Predefined.h"

bool WaveFunction::operator!=(const WaveFunction& _rhs) const
{
    if (!isWaveHeader(header)) return true;
    if (!isWaveHeader(_rhs.header)) return true;
    if (header.DATA_SIZE != _rhs.header.DATA_SIZE) return true;
    if (header.SAMPLE_RATE != _rhs.header.SAMPLE_RATE) return true;
    if (header.NUM_OF_CHANNEL != _rhs.header.NUM_OF_CHANNEL) return true;
    if (header.BIT_PER_SAMPLE != _rhs.header.BIT_PER_SAMPLE) return true;

    return false;
}

bool WaveFunction::operator==(const WaveFunction& _rhs) const
{
    return !(operator!=(_rhs));
}

WaveFunction WaveFunction::operator+(const WaveFunction& _rhs) const
{
    assert(operator==(_rhs));

    WaveFunction ret;
    ret.header = _rhs.header;
    ret.data.resize(data.size());

    for (int i = 0; i < data.size(); i++)
    {
        ret.data[i] = data[i] + _rhs.data[i];
    }

    return ret;
}

WaveFunction WaveFunction::operator-(const WaveFunction& _rhs) const
{
    assert(operator==(_rhs));

    WaveFunction ret;
    ret.header = _rhs.header;
    ret.data.resize(data.size());

    for (int i = 0; i < data.size(); i++)
    {
        ret.data[i] = data[i] - _rhs.data[i];
    }

    return ret;
}

WaveFunction WaveFunction::operator*(const WaveFunction& _rhs) const
{
    assert(operator==(_rhs));

    WaveFunction ret;
    ret.header = _rhs.header;
    ret.data.resize(data.size());

    for (unsigned long long i = 0; i < data.size(); i++)
    {
        ret.data[i] = data[i] * _rhs.data[i];
    }

    return ret;
}

bool WaveFunction::isWaveHeader(const WaveHeader& _header) const
{
    if (std::string(_header.RIFF, 4) != "RIFF") return false;
    if (std::string(_header.WAVE, 4) != "WAVE") return false;
    if (std::string(_header.FMT, 4) != "fmt ") return false;
    if (std::string(_header.DATA_ID, 4) != "data") return false;
    if ( _header.FMT_SIZE != 16) return false;
    if (_header.AUDIO_FORMAT != 1) return false;
    if (_header.NUM_OF_CHANNEL != 1) return false;

    return true;
}

bool WaveFunction::isWaveFile(const std::string& _fname) const
{
    std::ifstream file(_fname, std::ios::binary);
    if (!file) return false;

    WaveHeader head;
    file.read(reinterpret_cast<char*>(&head), sizeof(WaveHeader));
    if (!file) return false;

    return isWaveHeader(head);
}

bool WaveFunction::setWaveHeader(unsigned short _srate, unsigned short _sbit)
{
    if (_sbit % 8 != 0) return false;

    memcpy(header.RIFF, "RIFF", 4);
    memcpy(header.WAVE, "WAVE", 4);
    memcpy(header.FMT, "fmt ", 4);
    memcpy(header.DATA_ID, "data", 4);

    header.FMT_SIZE = 16;
    header.AUDIO_FORMAT = 1;
    header.NUM_OF_CHANNEL = 1;

    header.SAMPLE_RATE = _srate;
    header.BIT_PER_SAMPLE = _sbit;

    header.BLOCK_ALIGN = header.BIT_PER_SAMPLE / 8;
    header.BYTE_RATE = header.BLOCK_ALIGN * header.SAMPLE_RATE;

    header.DATA_SIZE = (unsigned int)data.size() * 2;
    header.CHUNK_SIZE = header.DATA_SIZE + 36;

    return true;
}

bool WaveFunction::setWaveData(const WaveData& _data)
{
    data.clear();
    data = _data;

    return true;
}

bool WaveFunction::setWaveFunction(const WaveData& _data, const WaveHeader& _header)
{
    return setWaveFunction(_data, _header.SAMPLE_RATE, _header.BIT_PER_SAMPLE);
}

bool WaveFunction::setWaveFunction(const WaveData& _data, unsigned short _srate, unsigned short _sbit)
{
    bool cond1 = setWaveData(_data);
    bool cond2 = setWaveHeader(_srate, _sbit);

    return cond1 && cond2;
}

bool WaveFunction::setWaveFunction(const WaveData& _data)
{
    return setWaveFunction(_data, header.SAMPLE_RATE, header.BIT_PER_SAMPLE);
}

bool WaveFunction::exportWave(const std::string& _fname) const
{
    std::ofstream file(_fname, std::ios::binary);

    if (!file) 
    {
        return false;
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * 2);

	return true;
}

bool WaveFunction::importWave(const std::string& _fname)
{
    if (isWaveFile(_fname))
    {
        std::ifstream file(_fname, std::ios::binary);

        header = WaveHeader();
        file.read(reinterpret_cast<char*>(&header), sizeof(WaveHeader));

        data.clear();
        data.resize(header.DATA_SIZE / 2);
        file.read(reinterpret_cast<char*>(data.data()), header.DATA_SIZE);

        if (file) return true;
    }

    header = WaveHeader();
    data.clear();

    return false;
}

WaveHeader WaveFunction::getWaveHeader() const
{
    return header;
}

WaveData WaveFunction::getWaveData() const
{
    return data;
}

WaveFunction WaveFunction::sin(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    WaveFunction ret;
    WaveData dat;

    assert(_namp < 1.0);
    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);
    double unit = 1.0 / (double)_srate;
    unsigned long long size = (unsigned long long)_dura * (unsigned long long)_srate;

    double tomg = 2.0 * PI * _freq;

    for (double i = 0; i < size; i++)
    {
        double sample = ramp * std::sin(tomg * i * unit);
        dat.push_back((short)sample);
    }
    
    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveFunction WaveFunction::sqr(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, double _duty)
{
    WaveFunction ret;
    WaveData dat;

    assert(_namp < 1.0);
    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);
    double unit = 1.0 / (double)_srate;
    double period = 1.0 / _freq;
    unsigned long long size = (unsigned long long)_dura * (unsigned long long)_srate;

    auto step = [period, ramp, _duty](double time)
        {
            double rem = time / period;
            rem -= floor(rem);

            if (rem < _duty) return ramp;
            return -ramp;
        };

    for (double i = 0; i < size; i++)
    {
        dat.push_back((short)step(unit * i));
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveFunction WaveFunction::tri(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit)
{
    WaveFunction ret;
    WaveData dat;

    assert(_namp < 1.0);
    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);
    double unit = 1.0 / (double)_srate;
    double period = 1.0 / _freq;
    unsigned long long size = (unsigned long long)_dura * (unsigned long long)_srate;

    auto step = [period, ramp](double time)
        {
            double rem = time / period;
            rem -= floor(rem);
            rem *= 4.0;

            if(rem > 1.0) return ramp * rem;
            else if(rem > 3.0) return ramp * (2.0 - rem);
            else return ramp * (rem - 4.0);
        };

    for (double i = 0; i < size; i++)
    {
        dat.push_back((short)step(unit * i));
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveFunction WaveFunction::saw(double _namp, double _freq, double _dura, unsigned short _srate, unsigned short _sbit, bool _reverse)
{
    WaveFunction ret;
    WaveData dat;

    assert(_namp < 1.0);
    double ramp = _namp * pow(2.0, (double)_sbit - 1.0);
    double unit = 1.0 / (double)_srate;
    double period = 1.0 / _freq;
    unsigned long long size = (unsigned long long)_dura * (unsigned long long)_srate;

    auto step = [period, ramp, _reverse](double time)
        {
            double rem = time / period;
            rem -= floor(rem);
            rem *= 2.0;

            if (_reverse) return ramp * (1.0 - rem);
            return ramp * (rem - 1.0);
        };

    for (double i = 0; i < size; i++)
    {
        dat.push_back((short)step(unit * i));
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}

WaveFunction WaveFunction::ofs(double _ofs, double _dura, unsigned short _srate, unsigned short _sbit)
{
    WaveFunction ret;
    WaveData dat;

    unsigned long long size = (unsigned long long)_dura * (unsigned long long)_srate;

    for (double i = 0; i < size; i++)
    {
        dat.push_back((short)_ofs);
    }

    ret.setWaveFunction(dat, _srate, _sbit);

    return ret;
}
