#include "param_rec.h"



BEGIN_MAVER_EMG_NAMESPACE

CParamRectifier::CParamRectifier() : CParam("ParamRectifier")
{
}


CParamRectifier::~CParamRectifier()
{
}

CParamRectifier::CParamRectifier(const CParamRectifier& rhs) : CParam(rhs)
{
	setParam(rhs.getParam());
}

CParamRectifier::CParamRectifier(const std::string& class_name) : CParam(class_name)
{}

CParamRectifier& CParamRectifier::operator= (const CParamRectifier& rhs)
{
	CParam::operator = (rhs);
	return *this;
}

CObject* CParamRectifier::clone() const
{
	return new CParamRectifier(*this);
}

std::shared_ptr<CObject> CParamRectifier::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParamRectifier::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamRectifier*>(ptr) != nullptr;
}

bool CParamRectifier::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

void CParamRectifier::setParam(RecParam param) {
	m_param = param;
}

RecParam CParamRectifier::getParam() const {
	return m_param;
}

END_MAVER_EMG_NAMESPACE
