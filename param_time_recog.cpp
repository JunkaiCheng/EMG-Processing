/* param of starttime recog param by Junwei Deng*/
#include <iostream>
#include "param_time_recog.h"
#include <assert.h>
#include <fstream>
#include "data.h"
BEGIN_MAVER_EMG_NAMESPACE

CParamTimeRecog::CParamTimeRecog() : CParam("CParamTimeRecog")
{
}

CParamTimeRecog::~CParamTimeRecog()
{}

CParamTimeRecog::CParamTimeRecog(const CParamTimeRecog& rhs):CParam(rhs)
{
	CParamTimeRecog::operator=(rhs);
}

CParamTimeRecog::CParamTimeRecog(const std::string& class_name):CParam(class_name)
{}

CParamTimeRecog& CParamTimeRecog::operator = (const CParamTimeRecog& rhs)
{
	CParam::operator=(rhs);
	setClassName(rhs.getClassName());
	this->J = rhs.J;
	this->cutoff_raw = rhs.cutoff_raw;
	this->cutoff_TKE = rhs.cutoff_TKE;
	this->order_raw = rhs.order_raw;
	this->order_TKE = rhs.order_TKE;
	this->sampling_frequency = rhs.sampling_frequency;
	this->windows_width = rhs.windows_width;
	this->quiet_mean = rhs.quiet_mean;
	this->quiet_std = rhs.quiet_std;
	return *this;
}

CObject* CParamTimeRecog::clone() const
{
	return new CParamTimeRecog(*this);
}

std::shared_ptr<CObject> CParamTimeRecog::clone_shared() const
{
	return std::make_shared<CParamTimeRecog>(*this);
}

bool CParamTimeRecog::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CParamTimeRecog*>(ptr) != nullptr;
}

bool CParamTimeRecog::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CParamTimeRecog::setparam(int SET_J, int SET_order_raw, int SET_order_TKE, int SET_cutoff_raw, int SET_cutoff_TKE, int SET_sampling_frequency, int SET_windows_width)
{
	if (!(SET_order_raw >= 1 && SET_order_raw <= 100 && SET_order_TKE >= 1 && SET_order_raw <= 100))
	{
		std::cout  << "filter order should be greater or equal to 1 and smaller or equal to 100, while your input order: " << SET_order_TKE << " or " << SET_order_raw << " is not allowed." << std::endl;
		assert(false);
	}
	if (!(SET_cutoff_raw > 0 && SET_cutoff_TKE > 0 && SET_cutoff_raw < SET_sampling_frequency && SET_cutoff_TKE < SET_sampling_frequency))
	{
		std::cout << "cutoff frequency should be greater than 0 and less than the sampling frequency, while your input cutoff frenquency: " << SET_cutoff_raw << " or " << SET_cutoff_TKE << " is not allowed" << std::endl;
		assert(false);
	}
	this->J = SET_J;
	this->order_raw = SET_order_raw;
	this->order_TKE = SET_order_TKE;
	this->cutoff_raw = SET_cutoff_raw;
	this->cutoff_TKE = SET_cutoff_TKE;
	this->sampling_frequency = SET_sampling_frequency;
	this->windows_width = SET_windows_width;
}

int CParamTimeRecog::getparam(const std::string& param_name) const
{
	if (param_name == "J")
	{
		return this->J;
	}
	if (param_name == "order_raw")
	{
		return this->order_raw;
	}
	if (param_name == "order_TKE")
	{
		return this->order_TKE;
	}
	if (param_name == "cutoff_raw")
	{
		return this->cutoff_raw;
	}
	if (param_name == "cutoff_TKE")
	{
		return this->cutoff_TKE;
	}
	if (param_name == "sampling_frequency")
	{
		return this->sampling_frequency;
	}
	if (param_name == "windows_width")
	{
		return this->windows_width;
	}
	std::cout << "Your input should be one of \"J\", \"order_raw\", \"order_TKE\", \"cutoff_raw\", \"cutoff_TKE\", \"windows_width\" and \"sampling_frequency, while your input: " << param_name << "is not one of them!" << std::endl;
	assert(false);
	return 0;
}

bool CParamTimeRecog::setwhitenoiseparam(const std::string& filename)
{
	std::ifstream in(filename);
	float s;
	if (!in.is_open())
	{
		return false;
	}
	CDataSeries vec;
	while (in >> s)
	{
		vec.push_back(s);
	}
	float sum = 0;
	float accum = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}
	float mean = float(sum) / vec.size();
	for (int i = 0; i < vec.size(); i++)
	{
		accum += (vec[i] - mean)*(vec[i] - mean);
	}
	float std = std::sqrt(accum / (vec.size() - 1));
	this->quiet_mean = mean;
	this->quiet_std = std;
	return true;
}

END_MAVER_EMG_NAMESPACE