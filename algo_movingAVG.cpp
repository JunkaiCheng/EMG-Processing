#include "algo_movingAVG.h"


BEGIN_MAVER_EMG_NAMESPACE


CAlgomovingAVG::CAlgomovingAVG() : CAlgo("AlgomovingAVG")
{
	m_param = std::make_shared<CParammovingAVG>("ParammovingAVG");
	m_output = std::make_shared<CDatamovingAVG>("DatamovingAVG");
}


CAlgomovingAVG::~CAlgomovingAVG()
{
}

CAlgomovingAVG::CAlgomovingAVG(const CAlgomovingAVG& rhs) : CAlgo(rhs)
{
	CAlgomovingAVG::operator=(rhs);
}

CAlgomovingAVG::CAlgomovingAVG(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParammovingAVG>("ParammovingAVG");
	m_output = std::make_shared<CDatamovingAVG>("DatamovingAVG");
}

CAlgomovingAVG& CAlgomovingAVG::operator = (const CAlgomovingAVG& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgomovingAVG::clone() const
{
	return new CAlgomovingAVG(*this);
}

std::shared_ptr<CObject> CAlgomovingAVG::clone_shared() const
{
	return std::make_shared<CAlgomovingAVG>(*this);
}

bool CAlgomovingAVG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgomovingAVG*>(ptr) != nullptr;
}

bool CAlgomovingAVG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgomovingAVG::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgomovingAVG::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		const CParam* par = input_param.get();
		const CParammovingAVG* tmp = dynamic_cast<const CParammovingAVG*>(par);
		m_param = std::make_shared<CParammovingAVG>(*tmp);
		return true;
	}
	else
		return false;
}

bool CAlgomovingAVG::execute()
{
	int size = m_input->getOutputData().size(); //通道数量
	int window = m_param->getParam(); //窗口大小

	m_output->resizeOutputData(size);
	
	for (int i = 0; i < size; ++i) {
		//对每一个通道进行滑动平均处理
		std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
		if (m_input->getDataSeries(i, *temp)) {
			std::shared_ptr<CDataSeries> result = std::make_shared<CDataSeries>();
			result->resize(temp->size());
			for (int j = 0; j < window - 1; ++j) {
				(*result)[j] = (*temp)[j];
			}
			for (int j = window - 1; j < temp->size(); ++j) {
				//对每一个窗口进行累加计算
				float sum = 0;
				for (int k = 0; k < window; ++k) {
					sum += (*temp)[j - k];
				}
				(*result)[j] = sum/window;
			}
			if (!m_output->setDataSeries(i, *result))
				return false;
		}
		else return false;
		}
	return true;
}

std::shared_ptr<CData> CAlgomovingAVG::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE
