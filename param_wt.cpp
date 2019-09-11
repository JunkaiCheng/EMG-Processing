// by yuanjian 2019-4-9

#include "param_wt.h"

BEGIN_MAVER_EMG_NAMESPACE

CParamWT::CParamWT() : CParam("Param")
{
	type = "sym9";		level = 1;
}

CParamWT::~CParamWT()
{}

CParamWT::CParamWT(const CParamWT& rhs) : CParam(rhs)
{
	type = rhs.type;		level = rhs.level;
}

CParamWT::CParamWT(const std::string& class_name) : CParam(class_name)
{
	type = "sym9";		level = 1;
}

CParamWT& CParamWT::operator= (const CParamWT& rhs)
{
	CParam::operator=(rhs);
	type = rhs.type;		level = rhs.level;
	return *this;
}

CObject* CParamWT::clone() const
{
	return new CParamWT(*this);
}

std::shared_ptr<CObject> CParamWT::clone_shared() const
{
	return std::make_shared<CParamWT>(*this);
}

bool CParamWT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamWT*>(ptr) != nullptr;
}

bool CParamWT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

void CParamWT::setValue(string type, int level) {
	this->type = type;	this->level = level;
}

END_MAVER_EMG_NAMESPACE