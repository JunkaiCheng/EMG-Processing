#include "data_lyapunov.h"


BEGIN_MAVER_EMG_NAMESPACE


CDataLyapunov::CDataLyapunov() : CData("DataLyapunov")
{
}


CDataLyapunov::~CDataLyapunov()
{
}

CDataLyapunov::CDataLyapunov(const CDataLyapunov& rhs) : CData(rhs)
{
}

CDataLyapunov::CDataLyapunov(const std::string& classname) : CData(classname)
{
}

CDataLyapunov& CDataLyapunov::operator = (const CDataLyapunov& rhs)
{
	setClassName(rhs.getClassName());
	CData::operator = (rhs);
	return *this;
}

CObject* CDataLyapunov::clone() const
{
	return new CDataLyapunov(*this);
}

bool CDataLyapunov::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataLyapunov*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CDataLyapunov::clone_shared() const
{
	return std::make_shared<CDataLyapunov>(*this);
}

bool CDataLyapunov::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

std::vector<LyaExp>& CDataLyapunov::getOutputData()
{
	return m_outputData;
}

void CDataLyapunov::setOutputData(std::vector<LyaExp>& output_data)
{
	m_outputData = output_data;
}

void CDataLyapunov::resizeOutputData(size_t resize_datasize)
{
	m_outputData.resize(resize_datasize);
}

bool CDataLyapunov::getDataSeries(size_t idx, LyaExp& data_series)
{
	if (idx >= m_outputData.size())
		return false;

	data_series = m_outputData[idx];
	return true;
}

bool CDataLyapunov::setDataSeries(size_t idx, LyaExp data_series)
{
	if (idx >= m_outputData.size())
		return false;

	m_outputData[idx] = data_series;
	return true;
}



END_MAVER_EMG_NAMESPACE
