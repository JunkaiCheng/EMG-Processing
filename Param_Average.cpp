#include "Param_Average.h"

BEGIN_MAVER_EMG_NAMESPACE


CParam_Average::CParam_Average() :CParam("CParam_Average")
{
}


CParam_Average::~CParam_Average()
{
}

CParam_Average::CParam_Average(const CParam_Average& rhs)
{
	CParam::CParam(rhs);
	dst_length = rhs.dst_length;
}
CParam_Average::CParam_Average(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_Average& CParam_Average::operator= (const CParam_Average& rhs)
{
	setClassName(rhs.getClassName());
	dst_length = rhs.dst_length;
	return *this;
}

CObject* CParam_Average::clone() const
{
	return new CParam_Average(*this);
}

std::shared_ptr<CObject> CParam_Average::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_Average::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_Average*>(ptr) != nullptr;
}

bool CParam_Average::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_Average::Set_dstLength(int value)
{
	dst_length = value;
}
int CParam_Average::Get_dstLength()
{
	return dst_length;
}


END_MAVER_EMG_NAMESPACE