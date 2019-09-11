#include "AlgoMVC.h"
#include <algorithm>

BEGIN_MAVER_EMG_NAMESPACE


CAlgoMVC::CAlgoMVC() : CAlgo("CAlgoMVC")
{
	m_param = std::make_shared<CParam_MVC>("Param MVC");
	m_output = std::make_shared<CData_MVC>("Data MVC");
}


CAlgoMVC::~CAlgoMVC()
{
}

CAlgoMVC::CAlgoMVC(const CAlgoMVC& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgoMVC::CAlgoMVC(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_MVC>("Param MVC");
	m_output = std::make_shared<CData_MVC>("Data MVC");
}

CAlgoMVC& CAlgoMVC::operator = (const CAlgoMVC& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgoMVC::clone() const
{
	return new CAlgoMVC(*this);
}

std::shared_ptr<CObject> CAlgoMVC::clone_shared() const
{
	return std::make_shared<CAlgoMVC>(*this);
}

bool CAlgoMVC::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoMVC*>(ptr) != nullptr;
}

bool CAlgoMVC::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoMVC::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoMVC::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param=std::make_shared<CParam_MVC>(*dynamic_cast<CParam_MVC*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgoMVC::execute()
{
	if (m_param->Get_MVCMethod() == "max")
	{
		std::vector<CDataSeries>	data;
		std::vector<CDataSeries> input_data = m_input->getOutputData();
		for (size_t i = 0; i < input_data.size(); i++)
		{
			std::vector<float> temp;
			auto maxposition = std::max_element(input_data[i].begin(), input_data[i].end());
			auto maxvalue = *maxposition;
			for (size_t j = 0; j < input_data[i].size(); j++)
				temp.push_back(input_data[i][j] / maxvalue);
			data.push_back(temp);
		}
		m_output->setOutputData(data);
	}
	
	return true;
}

std::shared_ptr<CData> CAlgoMVC::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE
