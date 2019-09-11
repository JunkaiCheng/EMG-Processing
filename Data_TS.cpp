#include "Data_TS.h"
BEGIN_MAVER_EMG_NAMESPACE

CData_TS::CData_TS() :CData("CData_TS")
{
}

CData_TS::~CData_TS()
{
}

CData_TS::CData_TS(const CData_TS& rhs) :CData(rhs)
{
}

CData_TS::CData_TS(const std::string& classname): CData(classname)
{

}

CData_TS& CData_TS::operator=(const CData_TS& rhs)
{
	CData::operator=(rhs);
	return *this;
}

CObject* CData_TS::clone() const
{
	return new CData_TS(*this);
}

bool CData_TS::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CData_TS*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_TS::clone_shared() const
{
	return std::make_shared<CData_TS>(*this);
}

bool CData_TS::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

END_MAVER_EMG_NAMESPACE
