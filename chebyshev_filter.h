//Junwei Deng with reference to the http://www.exstrom.com/journal/sigproc/
#ifndef CHEBYSHEV_FILTER_H
#define CHEBYSHEV_FILTER_H
#include <vector>

using namespace std;

bool chebyshev_lowpass(int order, float epsilon, float sf, float cutoff, const vector<float>& input, vector<float>& output);
bool chebyshev_highpass(int order, float epsilon, float sf, float cutoff, const vector<float>& input, vector<float>& output);
bool chebyshev_bandpass(int order, float epsilon, float sf, float upper_half_frequency, float lower_half_frequency, const vector<float>& input, vector<float>& output);
bool chebyshev_bandstop(int order, float epsilon, float sf, float upper_half_frequency, float lower_half_frequency, const vector<float>& input, vector<float>& output);
#endif // !CHEBYSHEV_FILTER_H

