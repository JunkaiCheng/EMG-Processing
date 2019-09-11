//Junwei Deng with reference to the http://www.exstrom.com/journal/sigproc/
#include "chebyshev_filter.h"
#include <math.h>
#include <iostream>
#define M_PI 3.1415926

//It works just like https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.cheby1.html
//the whole code is refer to http://www.exstrom.com/journal/sigproc/
//lowpass refer to: http://www.exstrom.com/journal/sigproc/cheblpf.c
//highpass refer to: http://www.exstrom.com/journal/sigproc/chebhpf.c
//bandpass refer to: http://www.exstrom.com/journal/sigproc/chebbpf.c
//bandstop refer to:http://www.exstrom.com/journal/sigproc/chebbsf.c
bool chebyshev_lowpass(int order, float epsilon, float sf, float cutoff, const vector<float>& input, vector<float>& output)
{
	int n = order;
	int m = n / 2;
	float ep = epsilon;
	float s = sf;
	float f = cutoff;
	float a = tan(M_PI*f / s);
	float a2 = a*a;
	float u = log((1.0 + sqrt(1.0 + ep*ep)) / ep);
	float su = sinh(u / (float)n);
	float cu = cosh(u / (float)n);
	float b, c;
	float *A = (float *)malloc(m * sizeof(float));
	float *d1 = (float *)malloc(m * sizeof(float));
	float *d2 = (float *)malloc(m * sizeof(float));
	float *w0 = (float *)calloc(m, sizeof(float));
	float *w1 = (float *)calloc(m, sizeof(float));
	float *w2 = (float *)calloc(m, sizeof(float));
	float x;
	for (int i = 0; i<m; ++i) {
		b = sin(M_PI*(2.0*i + 1.0) / (2.0*n))*su;
		c = cos(M_PI*(2.0*i + 1.0) / (2.0*n))*cu;
		c = b*b + c*c;
		s = a2*c + 2.0*a*b + 1.0;
		A[i] = a2 / (4.0*s); // 4.0
		d1[i] = 2.0*(1 - a2*c) / s;
		d2[i] = -(a2*c - 2.0*a*b + 1.0) / s;
	}
	ep = 2.0 / ep; // used to normalize
	for (int j = 0; j < input.size(); j++)
	{
		x = input[j];
		for (int i = 0; i<m; ++i) {
			w0[i] = d1[i] * w1[i] + d2[i] * w2[i] + x;
			x = A[i] * (w0[i] + 2.0*w1[i] + w2[i]);
			w2[i] = w1[i];
			w1[i] = w0[i];
		}
		output[j] = ep*x;
	}
	//free the memory 
	free(A);
	free(d1);
	free(d2);
	free(w0);
	free(w1);
	free(w2);
	return true;
}

bool chebyshev_highpass(int order, float epsilon, float sf, float cutoff, const vector<float>& input, vector<float>& output)
{
	int n = order;
	int m = n / 2;
	float ep = epsilon;
	float s = sf;
	float f = cutoff;
	float a = tan(M_PI*f / s);
	float a2 = a*a;
	float u = log((1.0 + sqrt(1.0 + ep*ep)) / ep);
	float su = sinh(u / (float)n);
	float cu = cosh(u / (float)n);
	float b, c;
	float *A = (float *)malloc(m * sizeof(float));
	float *d1 = (float *)malloc(m * sizeof(float));
	float *d2 = (float *)malloc(m * sizeof(float));
	float *w0 = (float *)calloc(m, sizeof(float));
	float *w1 = (float *)calloc(m, sizeof(float));
	float *w2 = (float *)calloc(m, sizeof(float));
	float x;

	for (int i = 0; i<m; ++i) {
		b = sin(M_PI*(2.0*i + 1.0) / (2.0*n))*su;
		c = cos(M_PI*(2.0*i + 1.0) / (2.0*n))*cu;
		c = b*b + c*c;
		s = a2 + 2.0*a*b + c;
		A[i] = 1.0 / (4.0*s); // 4.0
		d1[i] = 2.0*(c - a2) / s;
		d2[i] = -(a2 - 2.0*a*b + c) / s;
	}
	ep = 2.0 / ep; // used to normalize

	for (int j = 0; j < input.size(); j++)
	{
		x = input[j];
		for (int i = 0; i<m; ++i) {
			w0[i] = d1[i] * w1[i] + d2[i] * w2[i] + x;
			x = A[i] * (w0[i] - 2.0*w1[i] + w2[i]);
			w2[i] = w1[i];
			w1[i] = w0[i];
		}
		output[j] = ep*x;
	}
	free(A);
	free(d1);
	free(d2);
	free(w0);
	free(w1);
	free(w2);
	return true;
}

bool chebyshev_bandpass(int order, float epsilon, float sf, float upper_half_frequency, float lower_half_frequency, const vector<float>& input, vector<float>& output)
{
	int n = order;
	int m = n / 4;
	float ep = epsilon;
	float s = sf;
	float f1 = upper_half_frequency;
	float f2 = lower_half_frequency;
	float a = cos(M_PI*(f1 + f2) / s) / cos(M_PI*(f1 - f2) / s);
	float a2 = a*a;
	float b = tan(M_PI*(f1 - f2) / s);
	float b2 = b*b;
	float u = log((1.0 + sqrt(1.0 + ep*ep)) / ep);
	float su = sinh(2.0*u / (float)n);
	float cu = cosh(2.0*u / (float)n);
	float r, c;
	float *A = (float *)malloc(m * sizeof(float));
	float *d1 = (float *)malloc(m * sizeof(float));
	float *d2 = (float *)malloc(m * sizeof(float));
	float *d3 = (float *)malloc(m * sizeof(float));
	float *d4 = (float *)malloc(m * sizeof(float));
	float *w0 = (float *)calloc(m, sizeof(float));
	float *w1 = (float *)calloc(m, sizeof(float));
	float *w2 = (float *)calloc(m, sizeof(float));
	float *w3 = (float *)calloc(m, sizeof(float));
	float *w4 = (float *)calloc(m, sizeof(float));
	float x;

	for (int i = 0; i<m; ++i) {
		r = sin(M_PI*(2.0*i + 1.0) / n)*su;
		c = cos(M_PI*(2.0*i + 1.0) / n)*cu;
		c = r*r + c*c;
		s = b2*c + 2.0*b*r + 1.0;
		A[i] = b2 / (4.0*s); // 4.0
		d1[i] = 4.0*a*(1.0 + b*r) / s;
		d2[i] = 2.0*(b2*c - 2.0*a2 - 1.0) / s;
		d3[i] = 4.0*a*(1.0 - b*r) / s;
		d4[i] = -(b2*c - 2.0*b*r + 1.0) / s;
	}
	ep = 2.0 / ep; // used to normalize
	for (int j = 0; j < input.size(); j++)
	{
		x = input[j];
		for (int i = 0; i<m; ++i) {
			w0[i] = d1[i] * w1[i] + d2[i] * w2[i] + d3[i] * w3[i] + d4[i] * w4[i] + x;
			x = A[i] * (w0[i] - 2.0*w2[i] + w4[i]);
			w4[i] = w3[i];
			w3[i] = w2[i];
			w2[i] = w1[i];
			w1[i] = w0[i];
		}
		output[j] = ep*x;
	}

	return true;
}

bool chebyshev_bandstop(int order, float epsilon, float sf, float upper_half_frequency, float lower_half_frequency, const vector<float>& input, vector<float>& output)
{
	int n = order;
	int m = n / 4;
	float ep = epsilon;
	float s = sf;
	float f1 = upper_half_frequency;
	float f2 = lower_half_frequency;
	float a = cos(M_PI*(f1 + f2) / s) / cos(M_PI*(f1 - f2) / s);
	float a2 = a*a;
	float b = tan(M_PI*(f1 - f2) / s);
	float b2 = b*b;
	float u = log((1.0 + sqrt(1.0 + ep*ep)) / ep);
	float su = sinh(2.0*u / (float)n);
	float cu = cosh(2.0*u / (float)n);
	float r, c;
	float *A = (float *)malloc(m * sizeof(float));
	float *d1 = (float *)malloc(m * sizeof(float));
	float *d2 = (float *)malloc(m * sizeof(float));
	float *d3 = (float *)malloc(m * sizeof(float));
	float *d4 = (float *)malloc(m * sizeof(float));
	float *w0 = (float *)calloc(m, sizeof(float));
	float *w1 = (float *)calloc(m, sizeof(float));
	float *w2 = (float *)calloc(m, sizeof(float));
	float *w3 = (float *)calloc(m, sizeof(float));
	float *w4 = (float *)calloc(m, sizeof(float));
	float x;

	for (int i = 0; i<m; ++i) {
		r = sin(M_PI*(2.0*i + 1.0) / n)*su;
		c = cos(M_PI*(2.0*i + 1.0) / n)*cu;
		c = r*r + c*c;
		s = b2 + 2.0*b*r + c;
		A[i] = 1.0 / (4.0*s); // 4.0
		d1[i] = 4.0*a*(c + b*r) / s;
		d2[i] = 2.0*(b2 - 2.0*a2*c - c) / s;
		d3[i] = 4.0*a*(c - b*r) / s;
		d4[i] = -(b2 - 2.0*b*r + c) / s;
	}
	r = 4.0*a;
	s = 4.0*a2 + 2.0;

	ep = 2.0 / ep; // used to normalize

	for (int j = 0; j < input.size(); j++)
	{
		x = input[j];
		for (int i = 0; i<m; ++i) {
			w0[i] = d1[i] * w1[i] + d2[i] * w2[i] + d3[i] * w3[i] + d4[i] * w4[i] + x;
			x = A[i] * (w0[i] - r*w1[i] + s*w2[i] - r*w3[i] + w4[i]);
			w4[i] = w3[i];
			w3[i] = w2[i];
			w2[i] = w1[i];
			w1[i] = w0[i];
		}
		output[j] = ep*x;
	}
	return true;
}