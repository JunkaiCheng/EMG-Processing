#include "param_rms.h"



BEGIN_MAVER_EMG_NAMESPACE

CParamRMSFilter::CParamRMSFilter() : CParam("ParamRMSFilter")
{
}


CParamRMSFilter::~CParamRMSFilter()
{
}

CParamRMSFilter::CParamRMSFilter(const CParamRMSFilter& rhs) : CParam(rhs)
{
	setParam(rhs.getParam());
}

CParamRMSFilter::CParamRMSFilter(const std::string& class_name) : CParam(class_name)
{}

CParamRMSFilter& CParamRMSFilter::operator= (const CParamRMSFilter& rhs)
{
	setClassName(rhs.getClassName());
	CParam::operator = (rhs);
	return *this;
}

CObject* CParamRMSFilter::clone() const
{
	return new CParamRMSFilter(*this);
}

std::shared_ptr<CObject> CParamRMSFilter::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParamRMSFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamRMSFilter*>(ptr) != nullptr;
}

bool CParamRMSFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

void CParamRMSFilter::setParam(Length param) {
	m_param = param;
}

Length CParamRMSFilter::getParam() const{
	return m_param;
}

END_MAVER_EMG_NAMESPACE
