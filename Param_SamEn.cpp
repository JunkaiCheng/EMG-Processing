#include "Param_SamEn.h"

BEGIN_MAVER_EMG_NAMESPACE


CParam_SamEn::CParam_SamEn() :CParam("CParam_SamEn")
{
}


CParam_SamEn::~CParam_SamEn()
{
}

CParam_SamEn::CParam_SamEn(const CParam_SamEn& rhs)
{
	CParam::CParam(rhs);
	EnDim = rhs.EnDim;
	Tolerance = rhs.Tolerance;

}
CParam_SamEn::CParam_SamEn(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_SamEn& CParam_SamEn::operator= (const CParam_SamEn& rhs)
{
	setClassName(rhs.getClassName());
	EnDim = rhs.EnDim;
	Tolerance = rhs.Tolerance;
	return *this;
}

CObject* CParam_SamEn::clone() const
{
	return new CParam_SamEn(*this);
}

std::shared_ptr<CObject> CParam_SamEn::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_SamEn::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_SamEn*>(ptr) != nullptr;
}

bool CParam_SamEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_SamEn::SetEnDim(int temp)
{
	EnDim = temp;
}
int CParam_SamEn::GetEnDim()
{
	return EnDim;
}
void CParam_SamEn::SetTolerance(float temp)
{
	Tolerance = temp;
}
float CParam_SamEn::GetTolerance()
{
	return Tolerance;
}
END_MAVER_EMG_NAMESPACE
