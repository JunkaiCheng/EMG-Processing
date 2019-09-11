#include "Algo_IEMG.h"
using namespace MaverEMG;
CAlgo_IEMG::CAlgo_IEMG() : CAlgo("CAlgo_IEMG")
{
	m_param = std::make_shared<CParam_IEMG>("Param_IEMG");
	m_output = std::make_shared<CData_IEMG>("Data_IEMG");
}


CAlgo_IEMG::~CAlgo_IEMG()
{
}

CAlgo_IEMG::CAlgo_IEMG(const CAlgo_IEMG& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_IEMG::CAlgo_IEMG(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_IEMG>("Param_IEMG");
	m_output = std::make_shared<CData_IEMG>("Data_IEMG");
}


CAlgo_IEMG& CAlgo_IEMG::operator = (const CAlgo_IEMG& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_IEMG::clone() const
{
	return new CAlgo_IEMG(*this);
}

std::shared_ptr<CObject> CAlgo_IEMG::clone_shared() const
{
	return std::make_shared<CAlgo_IEMG>(*this);
}

bool CAlgo_IEMG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_IEMG*>(ptr) != nullptr;
}

bool CAlgo_IEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_IEMG::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_IEMG::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_IEMG>(*dynamic_cast<CParam_IEMG*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_IEMG::execute()
{
	int type = m_param->GetType();
	float IntValue = m_param->GetIntValue();
	std::vector<CDataSeries> input = m_input->getOutputData();
	CDataSeries temp;
	std::vector<CDataSeries> output;
	float int_sum = 0;
	if (type == 0)//time
	{
		int period = int(IntValue);
		for (size_t i = 0; i < input.size(); i++)
		{
			temp.clear();
			temp.push_back(0);
			int_sum = 0;
			for (size_t j = 1; j < input[i].size(); j++)
			{
				int_sum += (input[i][j] + input[i][j - 1]) / 2;
				temp.push_back(int_sum);
				if (j%period == 0)
				{
					int_sum = 0;
				}
			}
			output.push_back(temp);
			
		}
		m_output->setOutputData(output);
	}
	else//amplitude
	{
		for (size_t i = 0; i < input.size(); i++)
		{
			temp.clear();
			temp.push_back(0);
			int_sum = 0;
			for (size_t j = 1; j < input[i].size(); j++)
			{
				int_sum += (input[i][j] + input[i][j - 1]) / 2;
				temp.push_back(int_sum);
				if (int_sum>=IntValue)
				{
					int_sum = 0;
				}
			}
			output.push_back(temp);
		}
		m_output->setOutputData(output);
	}
	return true;
}

std::shared_ptr<CData> CAlgo_IEMG::getOutputData()
{
	return m_output;
}