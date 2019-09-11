#include "Param_RenyiEn.h"

BEGIN_MAVER_EMG_NAMESPACE


CParam_RenyiEn::CParam_RenyiEn() :CParam("CParam_RenyiEn")
{
}


CParam_RenyiEn::~CParam_RenyiEn()
{
}

CParam_RenyiEn::CParam_RenyiEn(const CParam_RenyiEn& rhs)
{
	CParam_RenyiEn::operator=(rhs);
}
CParam_RenyiEn::CParam_RenyiEn(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_RenyiEn& CParam_RenyiEn::operator= (const CParam_RenyiEn& rhs)
{
	CParam::operator=(rhs);
	SubSectionNum = rhs.SubSectionNum;
	Order = rhs.Order;
	return *this;
}

CObject* CParam_RenyiEn::clone() const
{
	return new CParam_RenyiEn(*this);
}

std::shared_ptr<CObject> CParam_RenyiEn::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_RenyiEn::isSameKindAs(const CObject* ptr)
{
	bool temp= dynamic_cast<const CParam_RenyiEn*>(ptr) != nullptr;
	return temp;
}

bool CParam_RenyiEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_RenyiEn::SetOrder(float temp)
{
	Order = temp;
}
float CParam_RenyiEn::GetOrder()
{
	return Order;
}
void CParam_RenyiEn::SetSubSectionNum(int temp)
{
	SubSectionNum = temp;
}
int CParam_RenyiEn::GetSubSectionNum()
{
	return SubSectionNum;
}
END_MAVER_EMG_NAMESPACE

