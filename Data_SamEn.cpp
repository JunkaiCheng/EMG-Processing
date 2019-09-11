#include "Data_SamEn.h"
BEGIN_MAVER_EMG_NAMESPACE
CData_SamEn::CData_SamEn() :CData("CData_SamEn")
{
}

CData_SamEn::~CData_SamEn()
{
}

CData_SamEn::CData_SamEn(const CData_SamEn& rhs) 
{
	CData_SamEn::operator=(rhs);
}

CData_SamEn::CData_SamEn(const std::string& classname) : CData(classname)
{

}

CData_SamEn& CData_SamEn::operator=(const CData_SamEn& rhs)
{
	CData::operator=(rhs);
	EnValue = rhs.EnValue;
	return *this;
}

CObject* CData_SamEn::clone() const
{
	return new CData_SamEn(*this);
}

bool CData_SamEn::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CData_SamEn*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_SamEn::clone_shared() const
{
	return std::make_shared<CData_SamEn>(*this);
}

bool CData_SamEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
CDataSeries CData_SamEn::GetEnValue()
{
	return EnValue;
}
void CData_SamEn::SetEnValue(CDataSeries temp)
{
	EnValue = temp;
}

END_MAVER_EMG_NAMESPACE