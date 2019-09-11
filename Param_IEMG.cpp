#include "Param_IEMG.h"

BEGIN_MAVER_EMG_NAMESPACE


CParam_IEMG::CParam_IEMG() :CParam("CParam_IEMG")
{
}


CParam_IEMG::~CParam_IEMG()
{
}

CParam_IEMG::CParam_IEMG(const CParam_IEMG& rhs)
{
	CParam::CParam(rhs);
	IntMethod = rhs.IntMethod;
	IntValue = rhs.IntValue;
	Type = rhs.Type;

}
CParam_IEMG::CParam_IEMG(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_IEMG& CParam_IEMG::operator= (const CParam_IEMG& rhs)
{
	setClassName(rhs.getClassName());
	IntMethod = rhs.IntMethod;
	IntValue = rhs.IntValue;
	Type = rhs.Type;
	return *this;
}

CObject* CParam_IEMG::clone() const
{
	return new CParam_IEMG(*this);
}

std::shared_ptr<CObject> CParam_IEMG::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_IEMG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParam_IEMG*>(ptr) != nullptr;
}

bool CParam_IEMG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_IEMG::SetIntMethod(std::string& temp)
{
	IntMethod = temp;
	if (temp == "time")
		Type = 0;
	else
	{
		Type = 1;
	}
}
int CParam_IEMG::GetType()
{
	return Type;
}
void CParam_IEMG::SetIntValue(float temp)
{
	IntValue = temp;
}
float CParam_IEMG::GetIntValue()
{
	return IntValue;
}
END_MAVER_EMG_NAMESPACE
