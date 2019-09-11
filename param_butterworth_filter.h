

#ifndef _MAVOR_EMG_PARAM_BUTTEROWRTH_FILTER_H_
#define _MAVOR_EMG_PARAM_BUTTEROWRTH_FILTER_H_

#include "param.h"
#include <string>
#include <vector>

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class CParamButterworthFilter: public CParam
{
public:
	CParamButterworthFilter();

	virtual ~CParamButterworthFilter();

	CParamButterworthFilter(const CParamButterworthFilter& rhs);

	CParamButterworthFilter(const std::string& class_name);

	CParamButterworthFilter& operator = (const CParamButterworthFilter& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

// -----------------------------------------------------------------------------------
// 此类独有信息
// -----------------------------------------------------------------------------------
public:
	// 第一种方式，设置截止频率和阶数。具体参数含义如下：
	//	-1. filter_type: 支持四种滤波器，lowpass, highpass, bandpass, bandstop
	//	-2. filter_order: butterworth滤波器的阶数，详见: http://www.exstrom.com/journal/sigproc/
	//	-3. scale_flag: True to scale, False to not scale ccof
	//	-4. f1f 和 f2f (cutoff frequency):
	//			If fs is the frequency at which the data is sampled (samples per second) and f is the cutoff frequency you want, 
	//			then the parameter you would input to the program is 2*f/fs. 
	//			For example if your data is sampled at 5000 samples/sec and you want a bandpass filter from 500 to 1000 Hz, 
	//			then the lower cutoff would be 2*500/5000=0.2 and the upper cutoff would be 2*1000/5000=0.4.
	//			值得注意的是，lowpass highpass 仅有 f1f 一个变量，bandpass bandstop 才用到 f1f 和 f2f
	//	-5. filename_coef: 所有的参数会保存为一个文件，然后直接读取该文件
	void setParams(string filter_type, int filter_order, bool scale_flag, float f1f, string filename_coef, float f2f = -1.0);

	// 第二种方法，读取本文
	void setParams(string filename_coef);

public: 
	//	IIR Digital Filter Functions
	//		An IIR filter is also known as a recursive digital filter because its output
	//		is a function of previous outputs as well as the input.If x[n] represents the
	//		nth input to the filter and y[n] is the nth output of the filter then a
	//		general iir filter is implemented as follows :
	//			y[n] = c0*x[n] + c1*x[n - 1] + ... + cM*x[n - M] - (d1*y[n - 1] + d2*y[n - 2] + ... + dN*y[n - N])
	//		This means that the nth output is a linear function of the nth input, the
	//		previous M inputs, and the previous N outputs.The c and d coefficients are
	//		calculated to give the filter a specific frequency response.The number of
	//		coefficients, M and N, will vary depending on the type of filter.There are
	//		many different kinds of iir filters and many different ways to calculate the
	//		coefficients.Listed below are filter types(currently only Butterworth
	//												   filters) and the functions that can be used to calculate the c and d
	//		coefficients for lowpass, highpass, bandpass, and bandstop implementations of
	//		the filter.

	// d coefficients: 
	vector<double> dcof;

	// c coefficients:
	vector<double> ccof;
};

// ---------------------------------------------------------------------------------------------------
// Butterworth Filter 需要调用的库函数
// ---------------------------------------------------------------------------------------------------
double *binomial_mult(int n, double *p);
double *trinomial_mult(int n, double *b, double *c);

// ---------------------------------------------------------------------------------------------------
// Butterworth Lowpass Filter
// ---------------------------------------------------------------------------------------------------
//	double *dcof_bwlp(int N, double fcf);
//	
//	This fuction calculates the d coefficients for a Butterworth lowpass
//	filter.The coefficients are returned as an array of doubles.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	fcf = filter cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A pointer to an array of doubles is returned.The size of the
//	array is equal to N + 1, one more than the filter order.The first
//	element of the array is d0, the coefficient of y[n], which will
//	always be equal to 1. The second element of the array is d1, the
//	coefficient of y[n - 1], and so on.The calling program must free
//	the array when finished with it.
double *dcof_bwlp(int n, double fcf);

//	int *ccof_bwlp(int n);
//	
//	This fuction calculates the c coefficients for a Butterworth lowpass
//	filter.The coefficients are returned as an array of integers.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	
//	Return value :
//	A pointer to an array of integers is returned.The size of the
//	array is equal to N + 1, one more than the filter order.The first
//	element of the array is c0, the coefficient of x[n], which is the
//	current input to the filter.The second element of the array is
//	c1, the coefficient of x[n - 1], and so on.The calling program
//	must free the array when finished with it.
double *ccof_bwlp(int n);

//	double sf_bwlp(int n, double fcf);
//	
//	This fuction calculates the scaling factor for a Butterworth lowpass
//	filter.The scaling factor is what the c coefficients must be
//	multiplied by so that the frequency response of the filter has a
//	maximum magnitude of 1.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	fcf = filter cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A double that is scaling factor.
double sf_bwlp(int n, double fcf);

// ---------------------------------------------------------------------------------------------------
// Butterworth Highpass Filter
// ---------------------------------------------------------------------------------------------------
//	double *dcof_bwhp(int N, double fcf);
//	
//	This fuction calculates the d coefficients for a Butterworth highpass
//	filter.The coefficients are returned as an array of doubles.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	fcf = filter cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A pointer to an array of doubles is returned.The size of the
//	array is equal to N + 1, one more than the filter order.The first
//	element of the array is d0, the coefficient of y[n], which will
//	always be equal to 1. The second element of the array is d1, the
//	coefficient of y[n - 1], and so on.The calling program must free
//	the array when finished with it.
double *dcof_bwhp(int n, double fcf);

//	int *ccof_bwhp(int n);
//	
//	This fuction calculates the c coefficients for a Butterworth highpass
//	filter.The coefficients are returned as an array of integers.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	
//	Return value :
//	A pointer to an array of integers is returned.The size of the
//	array is equal to N + 1, one more than the filter order.The first
//	element of the array is c0, the coefficient of x[n], which is the
//	current input to the filter.The second element of the array is
//	c1, the coefficient of x[n - 1], and so on.The calling program
//	must free the array when finished with it.
double *ccof_bwhp(int n);

//	double sf_bwhp(int n, double fcf);
//	
//	This fuction calculates the scaling factor for a Butterworth highpass
//	filter.The scaling factor is what the c coefficients must be
//	multiplied by so that the frequency response of the filter has a
//	maximum magnitude of 1.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	fcf = filter cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A double that is scaling factor.
double sf_bwhp(int n, double fcf);

// ---------------------------------------------------------------------------------------------------
// Butterworth Bandpass Filter
// ---------------------------------------------------------------------------------------------------
//	double *dcof_bwbp(int n, double f1f, double f2f);
//	
//	This fuction calculates the d coefficients for a Butterworth bandpass
//	filter.The coefficients are returned as an array of doubles.Note
//	that, although there is no upper limit on the filter order, if the
//	bandwidth, f2f - f1f, is very small, the coefficients returned may
//	not give the desired response due to numerical instability in the
//	calculation.This problem should not occure if the filter order is
//	kept less that or equal to 10. For very small bandwidths you should
//	always verify the frequency response using a program such as rffr.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	f1f = lower cutoff frequency as a fraction of pi.Range = [0, 1].
//	f2f = upper cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A pointer to an array of doubles is returned.The size of the
//	array is equal to 2N + 1, one more than twice the filter order.The
//	first element of the array is d0, the coefficient of y[n], which
//	will always be equal to 1. The second element of the array is d1,
//	the coefficient of y[n - 1], and so on.The calling program must
//	free the array when finished with it.
double *dcof_bwbp(int n, double f1f, double f2f);

//	int *ccof_bwbp(int n);
//	
//	This fuction calculates the c coefficients for a Butterworth bandpass
//	filter.The coefficients are returned as an array of integers.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	
//	Return value :
//	A pointer to an array of integers is returned.The size of the
//	array is equal to 2N + 1, one more than twice the filter order.The
//	first element of the array is c0, the coefficient of x[n], which
//	is the current input to the filter.The second element of the
//	array is c1, the coefficient of x[n - 1], and so on.The calling
//	program must free the array when finished with it.Note that ck
//	for all odd k, c1, c3, c5, and so on, will be equal to zero for
//	this filter.
double *ccof_bwbp(int n);

//	double sf_bwbp(int n, double f1f, double f2f);
//	
//	This fuction calculates the scaling factor for a Butterworth bandpass
//	filter.The scaling factor is what the c coefficients must be
//	multiplied by so that the frequency response of the filter has a
//	maximum magnitude of 1.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	f1f = lower cutoff frequency as a fraction of pi.Range = [0, 1].
//	f2f = upper cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A double that is scaling factor.
double sf_bwbp(int n, double f1f, double f2f);

// ---------------------------------------------------------------------------------------------------
// Butterworth Bandstop Filter
// ---------------------------------------------------------------------------------------------------
//	double *dcof_bwbs(int n, double f1f, double f2f);
//	
//	This fuction calculates the d coefficients for a Butterworth bandstop
//	filter.The coefficients are returned as an array of doubles.Note
//	that, although there is no upper limit on the filter order, if the
//	bandwidth, f2f - f1f, is very small, the coefficients returned may
//	not give the desired response due to numerical instability in the
//	calculation.This problem should not occure if the filter order is
//	kept less that or equal to 10. For very small bandwidths you should
//	always verify the frequency response using a program such as rffr.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	f1f = lower cutoff frequency as a fraction of pi.Range = [0, 1].
//	f2f = upper cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A pointer to an array of doubles is returned.The size of the
//	array is equal to 2N + 1, one more than twice the filter order.The
//	first element of the array is d0, the coefficient of y[n], which
//	will always be equal to 1. The second element of the array is d1,
//	the coefficient of y[n - 1], and so on.The calling program must
//	free the array when finished with it.
double *dcof_bwbs(int n, double f1f, double f2f);

//	double *ccof_bwbs(int n, double f1f, double f2f);
//	
//	This fuction calculates the c coefficients for a Butterworth bandstop
//	filter.The coefficients are returned as an array of doubles.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	f1f = lower cutoff frequency as a fraction of pi.Range = [0, 1].
//	f2f = upper cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A pointer to an array of doubles is returned.The size of the
//	array is equal to 2N + 1, one more than twice the filter order.The
//	first element of the array is c0, the coefficient of x[n], which
//	is the current input to the filter.The second element of the
//	array is c1, the coefficient of x[n - 1], and so on.The calling
//	program must free the array when finished with it.Note that ck
//	for all odd k, c1, c3, c5, and so on, will be equal to zero for
//	this filter.
double *ccof_bwbs(int n, double f1f, double f2f);

//	double sf_bwbs(int n, double f1f, double f2f);
//	
//	This fuction calculates the scaling factor for a Butterworth bandstop
//	filter.The scaling factor is what the c coefficients must be
//	multiplied by so that the frequency response of the filter has a
//	maximum magnitude of 1.
//	
//	Parameters:
//	N = filter order.Range = [1, 20 or more] no fixed upper limit.
//	f1f = lower cutoff frequency as a fraction of pi.Range = [0, 1].
//	f2f = upper cutoff frequency as a fraction of pi.Range = [0, 1].
//	
//	Return value :
//	A double that is scaling factor.
double sf_bwbs(int n, double f1f, double f2f);

END_MAVER_EMG_NAMESPACE

#endif // !_MAVOR_EMG_PARAM_BUTTEROWRTH_FILTER_H_

