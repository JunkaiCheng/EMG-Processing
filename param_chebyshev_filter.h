#ifndef PARAM_CHEBYSHEV_FILTER_H
#define PARAM_CHEBYSHEV_FILTER_H

#include "param.h"
#include <string>
BEGIN_MAVER_EMG_NAMESPACE
class CParamChebyshevFilter : public CParam
{
public:
	CParamChebyshevFilter();

	virtual ~CParamChebyshevFilter();

	CParamChebyshevFilter(const CParamChebyshevFilter& rhs);

	CParamChebyshevFilter(const std::string& class_name);

	CParamChebyshevFilter& operator = (const CParamChebyshevFilter& rhs);

public:
	CObject* clone() const;

	std::shared_ptr<CObject> clone_shared() const;

	bool isSameKindAs(const CObject* ptr);

	bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	//REQUIED:
	//        mode: should only be one of "lowpass", "highpass", "bandpass" and "bandstop"
	//        order: should be an even interger larger or equal to 2 
	//        epsilon: [0,1]
	//        sf: nothing
	//        cutoff: nothing
	//        f1: nothing
	//        f2: nothing
	//MODIFIED: this->mode, this->order, this->epsilon, this->sf, this->cutoff, this->f1, this->f2
	//DISCRIPTION: This function change the parameter of the chebyshev filter
	//ATTENTION: nothing
	//e.g.C_filter_param->setparam("bandpass", 12, 0.5088471399095875, 1000, 15, 15, 25);
	bool setparam(std::string SET_mode, int SET_order, float SET_epsilon, float SET_sf, float SET_cutoff, float SET_f1, float SET_f2);

	//REQUIED: param_name should only be one of "order", "epsilon", "sf", "cutoff", "f1", "f2"
	//MODIFIED: nothing
	//DISCRIPTION: return the parameter you request
	//ATTENTION: nothing
	//e.g.getparam("order")
	float getparam(const std::string& param_name) const;

public:
	std::string mode = "lowpass"; // only "lowpass", "highpass", "bandpass" and "bandstop" should be use in this parameter
private:
	int order = 10; // the order of the filter
	float epsilon = 0.5; // epsilon is the ripple parameter, if you want to use ripple parameter "rp" just like in python scipy.signal, you can use: epsilon = (10**(0.1*rp)-1)**0.5 
	float sf = 1000; // sampling frequency
	float cutoff = 10; // same unit with the sampling frequency, only be used with "lowpass" or "highpass", if you choose "bandpass" or "bandstop", this param will be ignored
	float f1 = 5; // upper half power frequency, same unit with the sampling frequency, only be used with "bandpass" or "bandstop", if you choose "lowpass" or "highpass", this param will be ignored
	float f2 = 15; // lower half power frequency, same unit with the sampling frequency, only be used with "bandpass" or "bandstop", if you choose "lowpass" or "highpass", this param will be ignored
};

END_MAVER_EMG_NAMESPACE
#endif // !PARAM_CHEBYSHEV_FILTER_H

