#include "algo_rec.h"


BEGIN_MAVER_EMG_NAMESPACE


CAlgoRectifier::CAlgoRectifier() : CAlgo("AlgoRectifier")
{
	m_param = std::make_shared<CParamRectifier>("ParamRectifier");
	m_output = std::make_shared<CDataRectifier>("DataRectifier");
}


CAlgoRectifier::~CAlgoRectifier()
{
}

CAlgoRectifier::CAlgoRectifier(const CAlgoRectifier& rhs) : CAlgo(rhs)
{}

CAlgoRectifier::CAlgoRectifier(const std::string& class_name) : CAlgo(class_name)
{}

CAlgoRectifier& CAlgoRectifier::operator = (const CAlgoRectifier& rhs)
{
	setClassName(rhs.getClassName());
	return *this;
}

CObject* CAlgoRectifier::clone() const
{
	return new CAlgoRectifier(*this);
}

std::shared_ptr<CObject> CAlgoRectifier::clone_shared() const
{
	return std::make_shared<CAlgoRectifier>(*this);
}

bool CAlgoRectifier::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoRectifier*>(ptr) != nullptr;
}

bool CAlgoRectifier::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoRectifier::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoRectifier::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		const CParam* par = input_param.get();
		const CParamRectifier* tmp = dynamic_cast<const CParamRectifier*>(par);
		m_param = std::make_shared<CParamRectifier>(*tmp);
		return true;
	}
	else
		return false;
}

bool CAlgoRectifier::execute()
{
	int size = m_input->getOutputData().size();
	m_output->resizeOutputData(size);

	//半波整流
	if (m_param->getParam() == 'h') {
		for (int i = 0; i < size; ++i) {
			std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
			if (m_input->getDataSeries(i, *temp)) {
				for (int j = 0; j < temp->size(); ++j) {
					if ((*temp)[j] < 0)
						(*temp)[j] = 0.0f;
				}
				if (!m_output->setDataSeries(i, *temp))
					return false;
			}
			else return false;
		}
		return true;
	}

	//全波整流
	else if (m_param->getParam() == 'f') {
		for (int i = 0; i < size; ++i) {
			std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
			if (m_input->getDataSeries(i, *temp)) {
				for (int j = 0; j < temp->size(); ++j) {
					if ((*temp)[j] < 0)
						(*temp)[j] = -(*temp)[j];
				}
				if (!m_output->setDataSeries(i, *temp))
					return false;
			}
			else return false;
		}
		return true;
	}
	return false;
}

std::shared_ptr<CData> CAlgoRectifier::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE
