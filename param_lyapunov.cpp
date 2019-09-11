#include "param_lyapunov.h"



BEGIN_MAVER_EMG_NAMESPACE

CParamLyapunov::CParamLyapunov() : CParam("ParamLyapunov")
{
}


CParamLyapunov::~CParamLyapunov()
{
}

CParamLyapunov::CParamLyapunov(const CParamLyapunov& rhs) : CParam(rhs)
{
	setParam(rhs.getParam());
}

CParamLyapunov::CParamLyapunov(const std::string& class_name) : CParam(class_name)
{}

CParamLyapunov& CParamLyapunov::operator= (const CParamLyapunov& rhs)
{
	CParam::operator = (rhs);
	return *this;
}

CObject* CParamLyapunov::clone() const
{
	return new CParamLyapunov(*this);
}

std::shared_ptr<CObject> CParamLyapunov::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParamLyapunov::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamLyapunov*>(ptr) != nullptr;
}

bool CParamLyapunov::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

void CParamLyapunov::setParam(Frequency param) {
	m_param = param;
}

Frequency CParamLyapunov::getParam() const {
	return m_param;
}

END_MAVER_EMG_NAMESPACE
