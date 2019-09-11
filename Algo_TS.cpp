#include "Algo_TS.h"
#include "algorithm.h"
#include<sstream>
#include <ap.h>
#include <interpolation.h>
#include<stdafx.h>

BEGIN_MAVER_EMG_NAMESPACE
std::string float2str2(float x)
{
	std::stringstream ss;
	ss << x;
	return ss.str();
}
std::string float_list_2_str(const std::vector<float>& srcx)
{
	std::string benginindex = "[";
	std::string endindex = "]";
	std::string val;
	for (size_t i = 0; i < srcx.size(); i++)
	{
		val += float2str2(srcx[i]) + std::string(",");
	}
	val = val.substr(0, val.size() - 1);
	return benginindex + val + endindex;
}
void interpolate(const std::vector<float> & srcx, const std::vector<float> & srcy, const std::vector<float> & dstx, std::vector<float> & dsty)
{
	if (srcx.empty() || srcy.empty() || srcx.empty())
	{
		dsty = srcy;
		return;
	}
	std::string srcxstr = float_list_2_str(srcx);
	std::string srcystr = float_list_2_str(srcy);
	alglib::real_1d_array xreal = srcxstr.c_str();
	alglib::real_1d_array yreal = srcystr.c_str();
	alglib::spline1dinterpolant spline;
	alglib::spline1dbuildcubic(xreal, yreal, spline);
	dsty.resize(dstx.size());
	for (size_t i = 0; i < dstx.size(); i++)
	{
		dsty[i] = static_cast<float>(alglib::spline1dcalc(spline, static_cast<double>(dstx[i])));
	}
}


CAlgo_TS::CAlgo_TS() : CAlgo("CAlgo_TS")
{
	m_param = std::make_shared<CParam_TS>("Param_TS");
	m_output = std::make_shared<CData_TS>("Data_TS");
}


CAlgo_TS::~CAlgo_TS()
{
}

CAlgo_TS::CAlgo_TS(const CAlgo_TS& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_TS::CAlgo_TS(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_TS>("Param_TS");
	m_output = std::make_shared<CData_TS>("Data_TS");
}


CAlgo_TS& CAlgo_TS::operator = (const CAlgo_TS& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_TS::clone() const
{
	return new CAlgo_TS(*this);
}

std::shared_ptr<CObject> CAlgo_TS::clone_shared() const
{
	return std::make_shared<CAlgo_TS>(*this);
}

bool CAlgo_TS::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_TS*>(ptr) != nullptr;
}

bool CAlgo_TS::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_TS::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_TS::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_TS>(*dynamic_cast<CParam_TS*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_TS::execute()
{
	int dst_length = m_param->Get_dstLength();
	std::vector<CDataSeries> input_data = m_input->getOutputData();
	std::vector<CDataSeries> output;
	std::vector<float> dst_x;
	for (size_t i = 0; i < input_data.size(); i++)
	{
		
		std::vector<float> dst_y;
		int src_length = input_data[i].size();
		for (int z = 0; z < dst_length;z++)
		{
			dst_x.push_back(float(src_length)/dst_length*float(z));
		}
		std::vector<float> src_x;
		for (int k = 0; k < src_length; k++)
		{
			src_x.push_back(float(k));
		}
		interpolate(src_x, input_data[i], dst_x, dst_y);
		output.push_back(dst_y);
		dst_y.clear();
		dst_x.clear();
	}
	m_output->setOutputData(output);
	return true;
}

std::shared_ptr<CData> CAlgo_TS::getOutputData()
{
	return m_output;
}



END_MAVER_EMG_NAMESPACE
