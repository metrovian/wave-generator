#include "WaveletTransform.h"
#include "Predefined.h"

double MorletFunction::getFourierDomainMorlet(double _freq, double _treso, unsigned long long _idx)
{
	double omega = 2.0 * PI * getFrequency(_idx);
	double sigma = 2.0 * PI * _freq;
	double ret = 1.0;
	double square = (sigma - omega) * _treso / 2.355;
	ret += exp(-sigma * sigma);
	ret -= 2.0 * exp(-3.0 / 4.0 * sigma * sigma);
	ret = 1.0 / sqrt(ret) / pow(PI, 1.0 / 4.0);
	ret *= exp(-1.0 / 2.0 * square * square);

	return ret;
}

WaveData MorletFunction::getMorletTransform(double _freq, double _treso)
{
	WaveData backup1 = wdata;
	FourierData backup2 = fdata;
	WaveData ret;

	for (unsigned long long i = 0; i < fdata.size(); ++i)
	{

		fdata[i] *= getFourierDomainMorlet(_freq, _treso, i);
	}

	ifft();

	ret = wdata;
	wdata = backup1;
	fdata = backup2;

	return ret;
}

MorletFunction::MorletFunction(const FourierFunction& _wave, double _freq, double _treso) : FourierFunction(_wave)
{
	tdata.push_back(getMorletTransform(_freq, _treso));
}

MorletFunction::MorletFunction(const FourierFunction& _wave, double _freq1, double _freq2, double _freso, double _treso) : FourierFunction(_wave)
{
	for (double freq = _freq1; freq < _freq2; freq *= _freso)
	{
		tdata.push_back(getMorletTransform(freq, _treso));
		freqs.push_back(freq);
	}
}

bool MorletFunction::exportWavelet(std::string _fname)
{
	if (tdata.size() == 0) return false;

	else
	{
		std::ofstream file(_fname + ".csv");

		if (!file)
		{
			return false;
		}

		file << ", ";

		for (unsigned long long j = 0; j < tdata.size(); ++j)
		{
			file << freqs[j] << ", ";
		}

		file << std::endl;

		for (unsigned long long i = 0; i < tdata[0].size(); ++i)
		{
			file << (double)i / (double)header.SAMPLE_RATE << ", ";

			for (unsigned long long j = 0; j < tdata.size(); ++j)
			{
				file << tdata[j][i] << ", ";
			}

			file << std::endl;
		}

		file.close();
	}

	return true;
}
