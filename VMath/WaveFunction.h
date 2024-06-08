#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

#pragma pack(push, 1)
struct WaveHeader
{
    char RIFF[4];                       // determined "RIFF"
    unsigned int CHUNK_SIZE;            // induced
    char WAVE[4];                       // determined "WAVE"
    char FMT[4];                        // determined "fmt "

    unsigned int FMT_SIZE;              // determined 16(PCM)
    unsigned short AUDIO_FORMAT;        // determined 1(PCM)
    unsigned short NUM_OF_CHANNEL;      // determined 1(MONO)
    unsigned int SAMPLE_RATE;           // user
    unsigned int BYTE_RATE;             // induced
    unsigned short BLOCK_ALIGN;         // induced
    unsigned short BIT_PER_SAMPLE;      // user
    char DATA_ID[4];                    // determined "data "
    unsigned int DATA_SIZE;             // induced
};
#pragma pack(pop)

typedef std::vector<short> WaveData;
class WaveFunction
{
public: /* data */
    WaveHeader header;
    WaveData data;

public: /* operator */
    bool operator!=(const WaveFunction& _rhs) const;
    bool operator==(const WaveFunction& _rhs) const;
    
    WaveFunction operator+(const WaveFunction& _rhs) const;
    WaveFunction operator-(const WaveFunction& _rhs) const;
    WaveFunction operator*(const WaveFunction& _rhs) const;

private: /* parts */
    bool isWaveHeader(const WaveHeader& _header) const;
    bool isWaveFile(const std::string& _fname) const;

    bool setWaveHeader(unsigned short _srate, unsigned short _sbit);
    bool setWaveData(const WaveData& _data);

public: /* public use */
    bool setWaveFunction(const WaveData& _data, const WaveHeader& _header);
    bool setWaveFunction(const WaveData& _data, unsigned short _srate, unsigned short _sbit);
    bool setWaveFunction(const WaveData& _data);

    bool exportWave(const std::string& _fname) const;
    bool importWave(const std::string& _fname);

    WaveHeader getWaveHeader() const;
    WaveData getWaveData() const;
};
