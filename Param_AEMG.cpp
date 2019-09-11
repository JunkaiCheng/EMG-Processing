#include "Param_AEMG.h"

BEGIN_MAVER_EMG_NAMESPACE


CParam_AEMG::CParam_AEMG() :CParam("CParam_AEMG")
{
}


CParam_AEMG::~CParam_AEMG()
{
}

CParam_AEMG::CParam_AEMG(const CParam_AEMG& rhs)
{
	CParam::CParam(rhs);
	
}
CParam_AEMG::CParam_AEMG(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_AEMG& CParam_AEMG::operator= (const CParam_AEMG& rhs)
{
	setClassName(rhs.getClassName());

	return *this;
}

CObject* CParam_AEMG::clone() const
{
	return new CParam_AEMG(*this);
}

std::shared_ptr<CObject> CParam_AEMG::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_AEMG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_AEMG*>(ptr) != nullptr;
}

bool CParam_AEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

END_MAVER_EMG_NAMESPACE
