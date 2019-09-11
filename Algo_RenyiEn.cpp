#include "Algo_RenyiEn.h"
#include<algorithm>
BEGIN_MAVER_EMG_NAMESPACE
static std::vector<int> GetSubsection(const CDataSeries& input,int sub_number)
{
	int size = input.size();
	std::vector<int> output;
	output.resize(sub_number,0);
	float start, end;
	auto maxposition = std::max_element(input.begin(), input.end());
	auto maxvalue = *maxposition;
	auto minposition = std::min_element(input.begin(), input.end());
	auto minvalue = *minposition;
	float sub_length = (maxvalue-minvalue) / sub_number;
	for (size_t i = 0; i < sub_number; i++)
	{
		start = minvalue + i*sub_length;
		end = minvalue + (i + 1)*sub_length;
		if (i == sub_number - 1)
			end += 0.01;
		for (size_t j = 0; j < input.size(); j++)
		{
			if (input[j] >= start&&input[j] < end)
				output[i] += 1;
		}
	}
	return output;
}
CAlgo_RenyiEn::CAlgo_RenyiEn() : CAlgo("CAlgo_RenyiEn")
{
	m_output = std::make_shared<CData_SamEn>("Data_RenyiEn");
	m_param = std::make_shared<CParam_RenyiEn>("Param_RenyiEn");
}


CAlgo_RenyiEn::~CAlgo_RenyiEn()
{
}

CAlgo_RenyiEn::CAlgo_RenyiEn(const CAlgo_RenyiEn& rhs) : CAlgo(rhs)
{
	CAlgo_RenyiEn::operator=(rhs);
}

CAlgo_RenyiEn::CAlgo_RenyiEn(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CData_SamEn>("Data_RenyiEn");
}


CAlgo_RenyiEn& CAlgo_RenyiEn::operator = (const CAlgo_RenyiEn& rhs)
{
	CAlgo::operator=(rhs);
	m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	m_output = std::dynamic_pointer_cast<CData_SamEn>(rhs.m_output->clone_shared());
	m_param = std::dynamic_pointer_cast<CParam_RenyiEn>(rhs.m_param->clone_shared());
	return *this;
}

CObject* CAlgo_RenyiEn::clone() const
{
	return new CAlgo_RenyiEn(*this);
}

std::shared_ptr<CObject> CAlgo_RenyiEn::clone_shared() const
{
	return std::make_shared<CAlgo_RenyiEn>(*this);
}

bool CAlgo_RenyiEn::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_RenyiEn*>(ptr) != nullptr;
}

bool CAlgo_RenyiEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_RenyiEn::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_RenyiEn::setParam(std::shared_ptr<CParam> input_param)
{
	
	if (input_param->isSameKindAs(m_param))
	{
		m_param = std::make_shared<CParam_RenyiEn>(*dynamic_cast<CParam_RenyiEn*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_RenyiEn::execute()
{
	int N = m_param->GetSubSectionNum();
	float order = m_param->GetOrder();
	std::vector<CDataSeries> data = m_input->getOutputData();
	CDataSeries output;
	CDataSeries temp;
	std::vector<int> SubSection;
	float RE;
	for (size_t i = 0; i < data.size(); i++)
	{
		temp = data[i];
		SubSection = GetSubsection(temp, N);
		RE = 0;
		for (size_t j = 0; j < SubSection.size(); j++)
		{
			RE += pow(SubSection[j] / float(temp.size()), order);
		}
		RE = RE / (1 - order);
		output.push_back(RE);
	}
	m_output->SetEnValue(output);
	return true;
}

std::shared_ptr<CData> CAlgo_RenyiEn::getOutputData()
{
	return m_output;
}



END_MAVER_EMG_NAMESPACE
