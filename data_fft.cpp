#include "data_fft.h"

BEGIN_MAVER_EMG_NAMESPACE

CDataFFT::CDataFFT() : CData("CDataFFT")
{}

CDataFFT::~CDataFFT()
{}

CDataFFT::CDataFFT(const CDataFFT& rhs) : CData(rhs)
{
	m_outputDataComplex = rhs.m_outputDataComplex;
}

CDataFFT::CDataFFT(const std::string& classname) : CData(classname)
{}

CDataFFT& CDataFFT::operator= (const CDataFFT& rhs)
{
	CData::operator=(rhs);
	m_outputDataComplex = rhs.m_outputDataComplex;
	return *this;
}

CObject* CDataFFT::clone() const
{
	return new CDataFFT(*this);
}

std::shared_ptr<CObject> CDataFFT::clone_shared() const
{
	return std::make_shared<CDataFFT>(*this);
}

bool CDataFFT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataFFT*>(ptr) != nullptr;
}

bool CDataFFT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return std::dynamic_pointer_cast<const CDataFFT, const CObject>(ptr) != nullptr;
}

std::vector<CDataSeriesCpx>& CDataFFT::getOutputDataComplex()
{
	return m_outputDataComplex;
}

bool CDataFFT::getDataSeriesComplex(size_t idx, CDataSeriesCpx& data_series)
{
	if (idx >= m_outputDataComplex.size())
		return false;
	data_series = m_outputDataComplex[idx];
	return true;
}

void CDataFFT::setOutputDataComplex(std::vector<CDataSeriesCpx>& output_data)
{
	m_outputDataComplex = output_data;
}

void CDataFFT::resizeOutputDataComplex(size_t resize_datasize)
{
	m_outputDataComplex.resize(resize_datasize);
}

bool CDataFFT::setDataSeriesComplex(size_t idx, CDataSeriesCpx& data_series)
{
	if (idx >= m_outputDataComplex.size())
		return false;

	m_outputDataComplex[idx] = data_series;
	return true;
}

END_MAVER_EMG_NAMESPACE
