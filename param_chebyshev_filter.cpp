#include "param_chebyshev_filter.h"
#include <iostream>
#include <assert.h>

BEGIN_MAVER_EMG_NAMESPACE

CParamChebyshevFilter::CParamChebyshevFilter() : CParam("CParamChebyshevFilter")
{
}

CParamChebyshevFilter::~CParamChebyshevFilter()
{}

CParamChebyshevFilter::CParamChebyshevFilter(const CParamChebyshevFilter& rhs) :CParam(rhs)
{
	CParamChebyshevFilter::operator=(rhs);
}

CParamChebyshevFilter::CParamChebyshevFilter(const std::string& class_name) : CParam(class_name)
{}

CParamChebyshevFilter& CParamChebyshevFilter::operator = (const CParamChebyshevFilter& rhs)
{
	CParam::operator=(rhs);
	setClassName(rhs.getClassName());
	this->mode = rhs.mode;
	this->order = rhs.order;
	this->epsilon = rhs.epsilon;
	this->cutoff = rhs.cutoff;
	this->f1 = rhs.f1;
	this->sf = rhs.sf;
	this->f2 = rhs.f2;
	return *this;
}

CObject* CParamChebyshevFilter::clone() const
{
	return new CParamChebyshevFilter(*this);
}

std::shared_ptr<CObject> CParamChebyshevFilter::clone_shared() const
{
	return std::make_shared<CParamChebyshevFilter>(*this);
}

bool CParamChebyshevFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CParamChebyshevFilter*>(ptr) != nullptr;
}

bool CParamChebyshevFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CParamChebyshevFilter::setparam(std::string SET_mode, int SET_order, float SET_epsilon, float SET_sf, float SET_cutoff, float SET_f1, float SET_f2)
{
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
	if (SET_mode != "lowpass" && SET_mode != "highpass" && SET_mode != "bandpass" && SET_mode != "bandstop")
	{
		std::cout << "mode: should only be one of \"lowpass\", \"highpass\", \"bandpass\" and \"bandstop\"" << std::endl;
		assert(false);
	}
	if (SET_order < 2 || SET_order % 2 != 0)
	{
		std::cout << "order: should be an even interger larger or equal to 2 " << std::endl;
		assert(false);
	}
	if (SET_epsilon > 1 || SET_epsilon < 0)
	{
		std::cout << "epsilon: [0,1]" << std::endl;
		assert(false);
	}
	this->mode = SET_mode;
	if (this->mode == "bandstop" || this->mode == "bandpass") //pay attention!!! this is for the identical with python scipy.signal
	{
		this->order = 2 * SET_order;
	}
	else
	{
		this->order = SET_order;
	}
	
	this->epsilon = SET_epsilon;
	this->cutoff = SET_cutoff;
	this->f1 = SET_f1;
	this->sf = SET_sf;
	this->f2 = SET_f2;
	return true;
}

float CParamChebyshevFilter::getparam(const std::string& param_name) const
{
	//REQUIED: param_name should only be one of "order", "epsilon", "sf", "cutoff", "f1", "f2"
	//MODIFIED: nothing
	//DISCRIPTION: return the parameter you request
	//ATTENTION: nothing
	//e.g.getparam("order")
	if (param_name == "order")
	{
		return this->order;
	}
	if (param_name == "sf")
	{
		return this->sf;
	}
	if (param_name == "f1")
	{
		return this->f1;
	}
	if (param_name == "f2")
	{
		return this->f2;
	}
	if (param_name == "epsilon")
	{
		return this->epsilon;
	}
	if (param_name == "cutoff")
	{
		return this->cutoff;
	}
	std::cout << "param_name should only be one of \"order\", \"epsilon\", \"sf\", \"cutoff\", \"f1\", \"f2\"" << std::endl;
	assert("false");
}

END_MAVER_EMG_NAMESPACE