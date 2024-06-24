#include "MIDI.h"
#include "Predefined.h"

void MIDI::inputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    switch (wMsg) 
    {

    case MIM_DATA: 
    {
        DWORD msg = dwParam1;
        BYTE status = msg & 0xFF;
        BYTE key = (msg >> 8) & 0xFF;
        BYTE velocity = (msg >> 16) & 0xFF;

        std::cout << "MIDI Message Received - Status: " << (int)status
            << ", Data1: " << (int)key
            << ", Data2: " << (int)velocity << std::endl;

        MIDI* device = reinterpret_cast<MIDI*>(dwInstance);

        if (status == 154)
        {
            std::thread trd_start = std::thread(&WaveFunction::playWave, &device->sound[(unsigned int)key - 21]);
            trd_start.detach();
        }

        if (status == 138)
        {
            std::thread trd_stop = std::thread(&WaveFunction::stopWave, &device->sound[(unsigned int)key - 21]);
            trd_stop.detach();
        }

        break;
    }

    default:
    {
        break;
    }
        
    }
}

bool MIDI::open(unsigned int _id)
{
    if (midiInOpen(&midi, _id, (DWORD_PTR)inputCallback, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) return false;
    return true;
}

bool MIDI::start()
{
    if (midiInStart(midi) != MMSYSERR_NOERROR) 
    {
        midiInClose(midi);
        return false;
    }

    return true;
}

bool MIDI::stop()
{
    if (midiInStop(midi) != MMSYSERR_NOERROR) return false;
    return true;
}

bool MIDI::close()
{
    if (midiInClose(midi) != MMSYSERR_NOERROR) return false;
    return true;
}

bool MIDI::setSound(WaveFunction(*_wave)(double _freq, double _dura), double _fdura)
{
    for (int i = 0; i < 88; i++)
    {
        sound[i] = _wave(A0 * pow(2.0, (double)i / 12.0), _fdura);
    }
}