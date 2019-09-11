#include "Data_IEMG.h"
BEGIN_MAVER_EMG_NAMESPACE

CData_IEMG::CData_IEMG() :CData("CData_IEMG")
{
}

CData_IEMG::~CData_IEMG()
{
}

CData_IEMG::CData_IEMG(const CData_IEMG&rhs) :CData(rhs)
{
	
}

CData_IEMG::CData_IEMG(const std::string &classname) : CData(classname)
{

}

CData_IEMG& CData_IEMG::operator=(const CData_IEMG& rhs)
{
	CData::operator=(rhs);
	return *this;
}

CObject* CData_IEMG::clone() const
{
	return new CData_IEMG(*this);
}

bool CData_IEMG::isSameKindAs(const CObject *ptr)
{
	return dynamic_cast<const CData_IEMG*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_IEMG::clone_shared() const
{
	return std::make_shared<CData_IEMG>(*this);
}

bool CData_IEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
END_MAVER_EMG_NAMESPACE
