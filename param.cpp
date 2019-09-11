//param object by maanbang 2019-3-31

#include "param.h"

BEGIN_MAVER_EMG_NAMESPACE

CParam::CParam() : CObject("Param")
{}

CParam::~CParam()
{}

CParam::CParam(const CParam& rhs) : CObject(rhs)
{

}

CParam::CParam(const std::string& class_name) : CObject(class_name)
{}

CParam& CParam::operator= (const CParam& rhs)
{
	setClassName(rhs.getClassName());
	return *this;
}

CObject* CParam::clone() const
{
	return new CParam(*this);
}

std::shared_ptr<CObject> CParam::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam*>(ptr) != nullptr;
}

bool CParam::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

END_MAVER_EMG_NAMESPACE