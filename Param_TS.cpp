#include "Param_TS.h"
BEGIN_MAVER_EMG_NAMESPACE


CParam_TS::CParam_TS() :CParam("CParam_TS")
{
}


CParam_TS::~CParam_TS()
{
}

CParam_TS::CParam_TS(const CParam_TS& rhs)
{
	CParam::CParam(rhs);
	dst_length = rhs.dst_length;
}
CParam_TS::CParam_TS(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_TS& CParam_TS::operator= (const CParam_TS& rhs)
{
	setClassName(rhs.getClassName());
	dst_length = rhs.dst_length;
	return *this;
}

CObject* CParam_TS::clone() const
{
	return new CParam_TS(*this);
}

std::shared_ptr<CObject> CParam_TS::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_TS::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_TS*>(ptr) != nullptr;
}

bool CParam_TS::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_TS::Set_dstLength(int value)
{
	dst_length = value;
}
int CParam_TS::Get_dstLength()
{
	return dst_length;
}


END_MAVER_EMG_NAMESPACE