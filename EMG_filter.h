#ifndef EMG_FILTER_H
#define EMG_FILTER_H

#include "include/DspFilters/Bessel.h"
#include "include/DspFilters/Butterworth.h"
#include "include/DspFilters/ChebyshevI.h"
#include "include/DspFilters/ChebyshevII.h"
#include "include/DspFilters/Elliptic.h"
#include <vector>

enum filterType { Lowpass, Highpass, Bandpass, Bandstop };

struct ParamButterworth {//lowpass use frequency_Low
	int order;
	double sampleRate;
	double frequency_Low;
	double frequency_High;
	filterType filter_Type;
};

struct ParamChebyshevI {
	int order;
	double sampleRate;
	double frequency_Low;
	double frequency_High;
	double rippleDb;
	filterType filter_Type;
};

struct ParamChebyshevII {
	int order;
	double sampleRate;
	double frequency_Low;
	double frequency_High;
	double stopBandDb;
	filterType filter_Type;
};

struct ParamElliptic {
	int order;
	double sampleRate;
	double frequency_Low;
	double frequency_High;
	double rippleDb;
	double rolloff;
	filterType filter_Type;
};

struct ParamBessel {
	int order;
	double sampleRate;
	double frequency_Low;
	double frequency_High;
	filterType filter_Type;
};
//ATTENTION: nothing, same as python
bool ButterworthFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamButterworth param);
//ATTENTION: nothing, same as python
bool ChebyshevIFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamChebyshevI param);
//ATTENTION: nothing, same as python
bool ChebyshevIIFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamChebyshevII param);
//ATTENTION: rolloff param is needed 
bool EllipticFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamElliptic param);
//ATTENTION: same as python in (norm = 'delay' mode)
bool BesselFilter(const std::vector<float>& in_data, std::vector<float>& out_data, struct ParamBessel param);

#endif // !EMG_FILTER_H


