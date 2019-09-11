#include "Data_MVC.h"

BEGIN_MAVER_EMG_NAMESPACE

CData_MVC::CData_MVC():CData("CData_MVC")
{
}

CData_MVC::~CData_MVC()
{
}

CData_MVC::CData_MVC(const CData_MVC&rhs) :CData(rhs)
{}

CData_MVC::CData_MVC(const std::string &classname) : CData(classname)
{

}

CData_MVC& CData_MVC::operator=(const CData_MVC& rhs)
{
	CData::operator=(rhs);
	return *this;
}

CObject* CData_MVC::clone() const
{
	return new CData_MVC(*this);
}

bool CData_MVC::isSameKindAs(const CObject *ptr)
{
	return dynamic_cast<const CData_MVC*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_MVC::clone_shared() const
{
	return std::make_shared<CData_MVC>(*this);
}

bool CData_MVC::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

END_MAVER_EMG_NAMESPACE
