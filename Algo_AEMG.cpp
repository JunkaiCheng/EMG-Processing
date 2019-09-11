#include "Algo_AEMG.h"
#include <math.h>
#include<algorithm>
BEGIN_MAVER_EMG_NAMESPACE

int sign(float x)
{
	if (x > 0)
		return 1;
	else
		return 0;
}
CAlgo_AEMG::CAlgo_AEMG() : CAlgo("CAlgo_AEMG")
{
	m_param = std::make_shared<CParam_AEMG>("Param AEMG");
	m_output = std::make_shared<CData_AEMG>("Data AEMG");
}


CAlgo_AEMG::~CAlgo_AEMG()
{
}

CAlgo_AEMG::CAlgo_AEMG(const CAlgo_AEMG& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_AEMG::CAlgo_AEMG(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_AEMG>("Param AEMG");
	m_output = std::make_shared<CData_AEMG>("Data AEMG");
}

CAlgo_AEMG& CAlgo_AEMG::operator = (const CAlgo_AEMG& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_AEMG::clone() const
{
	return new CAlgo_AEMG(*this);
}

std::shared_ptr<CObject> CAlgo_AEMG::clone_shared() const
{
	return std::make_shared<CAlgo_AEMG>(*this);
}

bool CAlgo_AEMG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_AEMG*>(ptr) != nullptr;
}

bool CAlgo_AEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_AEMG::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_AEMG::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_AEMG>(*dynamic_cast<CParam_AEMG*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_AEMG::execute()
{
	std::vector<CDataSeries> data = m_input->getOutputData();
	float sum;
	CDataSeries temp;
	for (size_t i = 0; i < data.size(); i++)
	{
		sum = 0;
		for (size_t j = 0; j < data[i].size(); j++)
		{
			sum += data[i][j];
		}
		temp.push_back(sum / data[i].size());
	}
	m_output->SetAEMG(temp);
	return true;
}
bool CAlgo_AEMG::execute_RMS()
{
	std::vector<CDataSeries> data = m_input->getOutputData();
	float sum;
	CDataSeries temp;
	for (size_t i = 0; i < data.size(); i++)
	{
		sum = 0;
		for (size_t j = 0; j < data[i].size(); j++)
		{
			sum += pow(data[i][j], 2);
		}
		temp.push_back(pow(sum / data[i].size(),0.5));
	}
	m_output->SetRMS(temp);
	return true;
}
bool CAlgo_AEMG::execute_MSD()
{
	execute_RMS();
	CDataSeries rms = m_output->GetRMS();
	std::vector<CDataSeries> data = m_input->getOutputData();
	float sum;
	CDataSeries temp;
	for (size_t i = 0; i < data.size(); i++)
	{
		sum = 0;
		for (size_t j = 0; j < data[i].size(); j++)
		{
			sum += pow(data[i][j]-rms[i], 2);
		}
		temp.push_back(sum/data[i].size());
	}
	m_output->SetMSD(temp);
	return true;
}
bool CAlgo_AEMG::execute_MaxVal()
{
	std::vector<CDataSeries> data = m_input->getOutputData();
	float max;
	CDataSeries temp;
	for (size_t i = 0; i < data.size(); i++)
	{
	
		auto maxposition = std::max_element(data[i].begin(), data[i].end());
		auto maxvalue = *maxposition;
		temp.push_back(maxvalue);
	}
	m_output->SetMaxVal(temp);
	return true;
}
bool CAlgo_AEMG::execute_CrossZeroRate()
{
	std::vector<CDataSeries> data = m_input->getOutputData();
	float Num=0;
	CDataSeries temp;
	for (size_t i = 0; i < data.size(); i++)
	{
		Num = 0;
		for (size_t j = 0; j < data[i].size() - 1; j++)
		{
			Num += sign(data[i][j] * data[i][j + 1]);
		}
		temp.push_back(Num / (float(data[i].size() - 1)));
	}
	m_output->SetCrossZeroRate(temp);
	return true;
}

std::shared_ptr<CData> CAlgo_AEMG::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE