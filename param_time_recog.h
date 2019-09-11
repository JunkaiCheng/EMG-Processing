/* param of starttime recog param by Junwei Deng*/

#ifndef __MAVER_EMG_ALGO_EMG_TIME_PARAM_H
#define __MAVER_EMG_ALGO_EMG_TIME_PARAM_H

#include "object.h"
#include "param.h"
#include <math.h>

BEGIN_MAVER_EMG_NAMESPACE

class CParamTimeRecog : public CParam
{
public:
	CParamTimeRecog();

	virtual ~CParamTimeRecog();

	CParamTimeRecog(const CParamTimeRecog& rhs);

	CParamTimeRecog(const std::string& class_name);

	CParamTimeRecog& operator = (const CParamTimeRecog& rhs);

public:
	CObject* clone() const;

	std::shared_ptr<CObject> clone_shared() const;

	bool isSameKindAs(const CObject* ptr);

	bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	//REQUIED: 1 <= SET_order_raw, SET_order_TKE <= 100, 0 < SET_cutoff_raw, SET_cutoff_TKE < sampeling_frequency
	//MODIFIED: *this
	//DISCRIPTION: this function change the parameter of our time recognizer, check the validation of parameter as well
	//ATTENTION: this function can't set the quiet_std and the quiet_mean
	//e.g.setparam(3, 6, 6, 20, 50, 1000)
	bool setparam(int SET_J, int SET_order_raw, int SET_order_TKE, int SET_cutoff_raw, int SET_cutoff_TKE, int SET_sampling_frequency, int SET_windows_width);

	//REQUIED: the param name you enter should be one of "J", "order_raw", "order_TKE", "cutoff_raw", "cutoff_TKE", "windows_width", and "sampling_frequency"
	//MODIFIED: nothing
	//DISCRIPTION: this function return the val of the time recognizer's param you want 
	//ATTENTION: the white noise's character (i.e. quiet_std and quiet_mean is changed to public variable), you can just visit them directly
	//e.g.getparam("order_raw");
	int getparam(const std::string& param_name) const;

	//REQUIED: the filename should be a file contain white noise (i.e. quiet sEMG signal)
	//MODIFIED: this->quiet_mean, this->quiet_std
	//DISCRIPTION: this function reset the parameters that concerned about the white noise
	//ATTENTION: nothing
	//e.g.setwhitenoiseparam("white_noise.txt")
	bool setwhitenoiseparam(const std::string& filename);

private:

	int J = 3; //default value is recommanded by Electromyogram analysis (William Rose)

	int order_raw = 6; //order_raw is the order of the butter filter carried on the raw signal

	int cutoff_raw = 20; //cutoff_raw is the cutoff frequency of the butter filter carried on the raw signal

	int order_TKE = 6; //order_TKE is the order of the butter filter carried on the TKE processed signal

	int cutoff_TKE = 50; //cutoff_TKE is the cutoff frequency of the butter filter carried on the TKE processed signal

	int sampling_frequency = 1000; //sampling_frequency is the sampling frequency of the signal

	int windows_width = 25; //how many data points we compare with the threshold
public:

	float quiet_std = 0.09731310146445557; // this is the Standard deviation of a "quiet" signal I generate

	float quiet_mean = 0.0501799313190681; //this is the mean of the "quiet" signal
};

END_MAVER_EMG_NAMESPACE

#endif // !__MAVER_EMG_ALGO_EMG_TIME_PARAM_H
