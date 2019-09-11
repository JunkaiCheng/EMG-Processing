#include "data.h"

BEGIN_MAVER_EMG_NAMESPACE

CData::CData() : CObject("Data")
{}

CData::~CData()
{}

CData::CData(const CData& rhs) : CObject(rhs)
{
	m_outputData = rhs.m_outputData;
}

CData::CData(const std::string& classname) : CObject(classname)
{
}

CData& CData::operator = (const CData& rhs)
{
	setClassName(rhs.getClassName());
	m_outputData = rhs.m_outputData;
	return *this;
}

CObject* CData::clone() const
{
	return new CData(*this);
}

bool CData::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CData*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData::clone_shared() const
{
	return std::make_shared<CData>(*this);
}

bool CData::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

std::vector<CDataSeries>& CData::getOutputData()
{
	return m_outputData;
}

void CData::setOutputData(std::vector<CDataSeries>& output_data)
{
	m_outputData = output_data;
}

void CData::resizeOutputData(size_t resize_datasize)
{
	m_outputData.resize(resize_datasize);
}

bool CData::getDataSeries(size_t idx, CDataSeries& data_series)
{
	if (idx >= m_outputData.size())
		return false;

	data_series = m_outputData[idx];
	return true;
}

bool CData::setDataSeries(size_t idx, CDataSeries& data_series)
{
	if (idx >= m_outputData.size())
		return false;

	m_outputData[idx] = data_series;
	return true;
}

END_MAVER_EMG_NAMESPACE