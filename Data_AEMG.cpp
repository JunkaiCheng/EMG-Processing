#include "Data_AEMG.h"
BEGIN_MAVER_EMG_NAMESPACE

CData_AEMG::CData_AEMG() :CData("CData_AEMG")
{
}

CData_AEMG::~CData_AEMG()
{
}

CData_AEMG::CData_AEMG(const CData_AEMG& rhs) :CData(rhs)
{
	AEMG = rhs.AEMG;
	RMS = rhs.RMS;
	MSD = rhs.MSD;
	CrossZeroRate = rhs.CrossZeroRate;
	MaxVal = rhs.MaxVal;
}

CData_AEMG::CData_AEMG(const std::string& classname) : CData(classname)
{

}

CData_AEMG& CData_AEMG::operator=(const CData_AEMG& rhs)
{
	CData::operator=(rhs);
	AEMG = rhs.AEMG;
	RMS = rhs.RMS;
	MSD = rhs.MSD;
	CrossZeroRate = rhs.CrossZeroRate;
	MaxVal = rhs.MaxVal;
	return *this;
}

CObject* CData_AEMG::clone() const
{
	return new CData_AEMG(*this);
}

bool CData_AEMG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CData_AEMG*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_AEMG::clone_shared() const
{
	return std::make_shared<CData_AEMG>(*this);
}

bool CData_AEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
CDataSeries CData_AEMG::GetAEMG()
{
	return AEMG;
}
void CData_AEMG::SetAEMG(const CDataSeries& temp)
{
	AEMG = temp;
}
CDataSeries CData_AEMG::GetRMS()
{
	return RMS;
}
void CData_AEMG::SetRMS(const CDataSeries& temp)
{
	RMS = temp;
}
CDataSeries CData_AEMG::GetMSD()
{
	return MSD;
}
void CData_AEMG::SetMSD(const CDataSeries& temp)
{
	MSD = temp;
}
CDataSeries CData_AEMG::GetCrossZeroRate()
{
	return CrossZeroRate;
}
void CData_AEMG::SetCrossZeroRate(const CDataSeries& temp)
{
	CrossZeroRate = temp;
}
CDataSeries CData_AEMG::GetMaxVal()
{
	return MaxVal;
}
void CData_AEMG::SetMaxVal(const CDataSeries& temp)
{
	MaxVal= temp;
}

END_MAVER_EMG_NAMESPACE
