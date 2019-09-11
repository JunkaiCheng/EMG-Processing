#include "algo_chebyshev_filter.h"
#include <iostream>
#include "chebyshev_filter.h"
BEGIN_MAVER_EMG_NAMESPACE


CAlgoChebyshevFilter::CAlgoChebyshevFilter() : CAlgo("CAlgoChebyshevFilter")
{
	this->m_input = std::make_shared<CData>("Chebyshev_Filter_input");
	this->m_output = std::make_shared<CData>("Chebyshev_Filter_output");
	this->m_param = std::make_shared<CParamChebyshevFilter>("Chebyshev_Filter_param");
}

CAlgoChebyshevFilter::~CAlgoChebyshevFilter()
{

}

CAlgoChebyshevFilter::CAlgoChebyshevFilter(const CAlgoChebyshevFilter& rhs) : CAlgo(rhs)
{
	this->m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = std::dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	this->m_param = std::dynamic_pointer_cast<CParamChebyshevFilter>(rhs.m_param->clone_shared());
}

CAlgoChebyshevFilter::CAlgoChebyshevFilter(const std::string& class_name) : CAlgo(class_name)
{
	this->m_input = std::make_shared<CData>("Chebyshev_Filter_input");
	this->m_output = std::make_shared<CData>("Chebyshev_Filter_output");
	this->m_param = std::make_shared<CParamChebyshevFilter>("Chebyshev_Filter_param");
}

CAlgoChebyshevFilter& CAlgoChebyshevFilter::operator = (const CAlgoChebyshevFilter& rhs)
{
	setClassName(rhs.getClassName());

	this->m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = std::dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	this->m_param = std::dynamic_pointer_cast<CParamChebyshevFilter>(rhs.m_param->clone_shared());
	return *this;
}

CObject* CAlgoChebyshevFilter::clone() const
{
	return new CAlgoChebyshevFilter(*this);
}

std::shared_ptr<CObject> CAlgoChebyshevFilter::clone_shared() const
{
	return std::make_shared<CAlgoChebyshevFilter>(*this);
}

bool  CAlgoChebyshevFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CAlgoChebyshevFilter*>(ptr) != nullptr;
}

bool CAlgoChebyshevFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoChebyshevFilter::setInputData(std::shared_ptr<CData> input_data)
{
	this->m_input = input_data;
	return true;
}

bool CAlgoChebyshevFilter::setParam(std::shared_ptr<CParamChebyshevFilter> input_param)
{
	this->m_param = input_param;
	return true;
}

bool CAlgoChebyshevFilter::execute()
{
	this->m_output->resizeOutputData(this->m_input->getOutputData().size());
	CDataSeries input; //used to hold one input signal
	CDataSeries output; //used to hold one output signal
	int count = 0;
	//filter the signal one by one
	while (this->m_input->getDataSeries(count, input))
	{
		output.clear();
		output.resize(input.size());
		//choose which filter to use
		if(this->m_param->mode == "lowpass")
			chebyshev_lowpass(this->m_param->getparam("order"), this->m_param->getparam("epsilon"), this->m_param->getparam("sf"), this->m_param->getparam("cutoff"), input, output);
		if(this->m_param->mode == "highpass")
			chebyshev_highpass(this->m_param->getparam("order"), this->m_param->getparam("epsilon"), this->m_param->getparam("sf"), this->m_param->getparam("cutoff"), input, output);
		if (this->m_param->mode == "bandpass")
			chebyshev_bandpass(this->m_param->getparam("order"), this->m_param->getparam("epsilon"), this->m_param->getparam("sf"), this->m_param->getparam("f2"), this->m_param->getparam("f1"), input, output);
		if (this->m_param->mode == "bandstop")
			chebyshev_bandstop(this->m_param->getparam("order"), this->m_param->getparam("epsilon"), this->m_param->getparam("sf"), this->m_param->getparam("f2"), this->m_param->getparam("f1"), input, output);
		this->m_output->setDataSeries(count, output);
		count++;
	}
	return true;
}

std::shared_ptr<CData> CAlgoChebyshevFilter::getOutputData()
{
	return this->m_output;
}

END_MAVER_EMG_NAMESPACE