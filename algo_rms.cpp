#include "algo_rms.h"
#include <numeric>

BEGIN_MAVER_EMG_NAMESPACE


CAlgoRMSFilter::CAlgoRMSFilter() : CAlgo("AlgoRMSFilter")
{
	m_param = std::make_shared<CParamRMSFilter>("ParamRMSFilter");
	m_output = std::make_shared<CDataRMSFilter>("DataRMSFilter");
}


CAlgoRMSFilter::~CAlgoRMSFilter()
{
}

CAlgoRMSFilter::CAlgoRMSFilter(const CAlgoRMSFilter& rhs) : CAlgo(rhs)
{
	CAlgoRMSFilter::operator=(rhs);
}

CAlgoRMSFilter::CAlgoRMSFilter(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParamRMSFilter>("ParamRMSFilter");
	m_output = std::make_shared<CDataRMSFilter>("DataRMSFilter");
}

CAlgoRMSFilter& CAlgoRMSFilter::operator = (const CAlgoRMSFilter& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgoRMSFilter::clone() const
{
	return new CAlgoRMSFilter(*this);
}

std::shared_ptr<CObject> CAlgoRMSFilter::clone_shared() const
{
	return std::make_shared<CAlgoRMSFilter>(*this);
}

bool CAlgoRMSFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoRMSFilter*>(ptr) != nullptr;
}

bool CAlgoRMSFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoRMSFilter::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoRMSFilter::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		const CParam* par = input_param.get();
		const CParamRMSFilter* tmp = dynamic_cast<const CParamRMSFilter*>(par);
		m_param = std::make_shared<CParamRMSFilter>(*tmp);
		return true;
	}
	else
		return false;
}

bool CAlgoRMSFilter::execute()
{
	int size = m_input->getOutputData().size(); //通道数量
	int window = m_param->getParam(); //窗口大小

	m_output->resizeOutputData(size);

	for (int i = 0; i < size; ++i) {
		std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
		
		if (m_input->getDataSeries(i, *temp)) {
			//计算平方值
			float sum = std::accumulate(std::begin(*temp), std::end(*temp), 0.0);
			float mean = sum / temp->size(); 
			for (int j = 0; j < temp->size(); ++j) {
				(*temp)[j] = ((*temp)[j] - mean)*((*temp)[j] - mean);
			}
			std::shared_ptr<CDataSeries> result = std::make_shared<CDataSeries>();
			result->resize(temp->size());
			for (int j = 0; j < window - 1; ++j) {
				(*result)[j] = (*temp)[j];
			}
			for (int j = window - 1; j < temp->size(); ++j) {
				//对每一个窗口计算平方根
				float sum = 0;
				for (int k = 0; k < window; ++k) {
					sum += (*temp)[j - k];
				}
				(*result)[j] = sqrt(sum / window);
			}
			if (!m_output->setDataSeries(i, *result))
				return false;
		} 
		else return false;
	}
	return true;
}

std::shared_ptr<CData> CAlgoRMSFilter::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE
