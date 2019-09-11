#include "Param_MVC.h"
BEGIN_MAVER_EMG_NAMESPACE


CParam_MVC::CParam_MVC():CParam("CParam_MVC")
{
	my_method = "max";
}


CParam_MVC::~CParam_MVC()
{
}

CParam_MVC::CParam_MVC(const CParam_MVC &rhs) 
{
	CParam::CParam(rhs);
	my_method = rhs.my_method;
}
CParam_MVC::CParam_MVC(const std::string&class_name)
{
	CParam::CParam(class_name);
	my_method = "max";
}

CParam_MVC& CParam_MVC::operator= (const CParam_MVC& rhs)
{
	setClassName(rhs.getClassName());
	my_method = rhs.my_method;
	return *this;
}

CObject* CParam_MVC::clone() const
{
	return new CParam_MVC(*this);
}

std::shared_ptr<CObject> CParam_MVC::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_MVC::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_MVC*>(ptr) != nullptr;
}

bool CParam_MVC::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_MVC::Set_MVCMethod(std::string&method)
{
	my_method = method;
}
std::string CParam_MVC::Get_MVCMethod()
{
	return my_method;
}


END_MAVER_EMG_NAMESPACE