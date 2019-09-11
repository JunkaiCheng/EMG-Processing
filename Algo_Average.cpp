#include "Algo_Average.h"
#include "AlgoMVC.h"
#include "Algo_TS.h"
BEGIN_MAVER_EMG_NAMESPACE


CAlgo_Average::CAlgo_Average() : CAlgo("CAlgo_Average")
{
	m_param = std::make_shared<CParam_Average>("Param Average");
	m_output = std::make_shared<CData_Average>("Data Average");
}


CAlgo_Average::~CAlgo_Average()
{
}

CAlgo_Average::CAlgo_Average(const CAlgo_Average& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_Average::CAlgo_Average(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_Average>("Param Average");
	m_output = std::make_shared<CData_Average>("Data Average");
}

CAlgo_Average& CAlgo_Average::operator = (const CAlgo_Average& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_Average::clone() const
{
	return new CAlgo_Average(*this);
}

std::shared_ptr<CObject> CAlgo_Average::clone_shared() const
{
	return std::make_shared<CAlgo_Average>(*this);
}

bool CAlgo_Average::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_Average*>(ptr) != nullptr;
}

bool CAlgo_Average::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_Average::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_Average::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_Average>(*dynamic_cast<CParam_Average*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_Average::execute()
{
	int DstLength = m_param->Get_dstLength();
	CAlgoMVC mvc;
	mvc.setInputData(m_input);
	std::shared_ptr<CParam_MVC> mvc_param = std::make_shared<CParam_MVC>();
	mvc.setParam(mvc_param);
	mvc.execute();
	CAlgo_TS ts;
	std::shared_ptr<CParam_TS> ts_param = std::make_shared<CParam_TS>();
	ts_param->Set_dstLength(DstLength);
	ts.setParam(ts_param);
	ts.setInputData(mvc.getOutputData());
	ts.execute();
	std::shared_ptr<CData> ts_out = ts.getOutputData();
	std::vector<CDataSeries> series_out = ts_out->getOutputData();
	float sum;
	std::vector<float> mean_list;

	
		for (size_t i = 0; i < DstLength; i++)
		{
			sum = 0;
			for (size_t j = 0; j < series_out.size(); j++)
			{
				sum += series_out[j][i];
			}
			mean_list.push_back(sum / series_out.size());
		}
		m_output->setOutputData(series_out);
		m_output->SetMeanList(mean_list);




	

	return true;
}

std::shared_ptr<CData> CAlgo_Average::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE