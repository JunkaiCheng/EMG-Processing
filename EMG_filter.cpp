#include "EMG_filter.h"
#include <iostream>
bool ButterworthFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamButterworth param)
{
	int numSamples = in_data.size();
	float* audioData[1];
	audioData[0] = new float[numSamples];
	out_data.resize(in_data.size());

	if (!in_data.empty())
		memcpy(audioData[0], &in_data[0], in_data.size() * sizeof(float));
	else
		return false;

	switch (param.filter_Type)
	{
	case Lowpass:
	{
		Dsp::SimpleFilter <Dsp::Butterworth::LowPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_Low
		);
		f.process(numSamples, audioData);
		break;
	}
	case Highpass:
	{
		Dsp::SimpleFilter <Dsp::Butterworth::HighPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_High
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandpass:
	{
		Dsp::SimpleFilter <Dsp::Butterworth::BandPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High)/2,
			(param.frequency_High - param.frequency_Low)
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandstop:
	{
		Dsp::SimpleFilter <Dsp::Butterworth::BandStop <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low)
		);
		f.process(numSamples, audioData);
		break;
	}
	default:
		return false;
	}
	memcpy(&out_data[0], audioData[0], in_data.size() * sizeof(float));
	return true;
}

bool ChebyshevIFilter(const std::vector<float>& in_data, std::vector<float>& out_data, ParamChebyshevI param)
{
	int numSamples = in_data.size();
	float* audioData[1];
	audioData[0] = new float[numSamples];
	out_data.resize(in_data.size());

	if (!in_data.empty())
		memcpy(audioData[0], &in_data[0], in_data.size() * sizeof(float));
	else
		return false;

	switch (param.filter_Type)
	{
	case Lowpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevI::LowPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_Low,
			param.rippleDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Highpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevI::HighPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_High,
			param.rippleDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevI::BandPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.rippleDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandstop:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevI::BandStop <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.rippleDb
		);
		f.process(numSamples, audioData);
		break;
	}
	default:
		return false;
	}
	memcpy(&out_data[0], audioData[0], in_data.size() * sizeof(float));
	return true;
}

bool ChebyshevIIFilter(const std::vector<float>& in_data, std::vector<float>& out_data, ParamChebyshevII param)
{
	int numSamples = in_data.size();
	float* audioData[1];
	audioData[0] = new float[numSamples];
	out_data.resize(in_data.size());

	if (!in_data.empty())
		memcpy(audioData[0], &in_data[0], in_data.size() * sizeof(float));
	else
		return false;

	switch (param.filter_Type)
	{
	case Lowpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevII::LowPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_Low,
			param.stopBandDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Highpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevII::HighPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_High,
			param.stopBandDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandpass:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevII::BandPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.stopBandDb
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandstop:
	{
		Dsp::SimpleFilter <Dsp::ChebyshevII::BandStop <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.stopBandDb
		);
		f.process(numSamples, audioData);
		break;
	}
	default:
		return false;
	}
	memcpy(&out_data[0], audioData[0], in_data.size() * sizeof(float));
	return true;
}

bool EllipticFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamElliptic param)
{
	int numSamples = in_data.size();
	float* audioData[1];
	audioData[0] = new float[numSamples];
	out_data.resize(in_data.size());

	if (!in_data.empty())
		memcpy(audioData[0], &in_data[0], in_data.size() * sizeof(float));
	else
		return false;
	switch (param.filter_Type)
	{
	case Lowpass:
	{
		Dsp::SimpleFilter <Dsp::Elliptic::LowPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_Low,
			param.rippleDb,
			param.rolloff
		);
		f.process(numSamples, audioData);
		break;
	}
	case Highpass:
	{
		Dsp::SimpleFilter <Dsp::Elliptic::HighPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_High,
			param.rippleDb,
			param.rolloff
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandpass:
	{
		Dsp::SimpleFilter <Dsp::Elliptic::BandPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.rippleDb,
			param.rolloff
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandstop:
	{
		Dsp::SimpleFilter <Dsp::Elliptic::BandStop <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low),
			param.rippleDb,
			param.rolloff
		);
		f.process(numSamples, audioData);
		break;
	}
	default:
		return false;
	}
	memcpy(&out_data[0], audioData[0], in_data.size() * sizeof(float));
	return true;
}

bool BesselFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamBessel param)
{
	int numSamples = in_data.size();
	float* audioData[1];
	audioData[0] = new float[numSamples];
	out_data.resize(in_data.size());

	if (!in_data.empty())
		memcpy(audioData[0], &in_data[0], in_data.size() * sizeof(float));
	else
		return false;

	switch (param.filter_Type)
	{
	case Lowpass:
	{
		Dsp::SimpleFilter <Dsp::Bessel::LowPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_Low
		);
		f.process(numSamples, audioData);
		break;
	}
	case Highpass:
	{
		Dsp::SimpleFilter <Dsp::Bessel::HighPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			param.frequency_High
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandpass:
	{
		Dsp::SimpleFilter <Dsp::Bessel::BandPass <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low)
		);
		f.process(numSamples, audioData);
		break;
	}
	case Bandstop:
	{
		Dsp::SimpleFilter <Dsp::Bessel::BandStop <100>, 1> f; //max order is 100
		f.setup(
			param.order,
			param.sampleRate,
			(param.frequency_Low + param.frequency_High) / 2,
			(param.frequency_High - param.frequency_Low)
		);
		f.process(numSamples, audioData);
		break;
	}
	default:
		return false;
	}
	memcpy(&out_data[0], audioData[0], in_data.size() * sizeof(float));
	return true;
}