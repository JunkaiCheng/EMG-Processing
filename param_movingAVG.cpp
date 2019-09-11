#include "param_movingAVG.h"



BEGIN_MAVER_EMG_NAMESPACE

CParammovingAVG::CParammovingAVG() : CParam("ParammovingAVG")
{
}


CParammovingAVG::~CParammovingAVG()
{
}

CParammovingAVG::CParammovingAVG(const CParammovingAVG& rhs) : CParam(rhs)
{
	setParam(rhs.getParam());
}

CParammovingAVG::CParammovingAVG(const std::string& class_name) : CParam(class_name)
{}

CParammovingAVG& CParammovingAVG::operator= (const CParammovingAVG& rhs)
{
	setClassName(rhs.getClassName());
	//setParam(rhs.getParam());
	CParam::operator = (rhs);
	return *this;
}

CObject* CParammovingAVG::clone() const
{
	return new CParammovingAVG(*this);
}

std::shared_ptr<CObject> CParammovingAVG::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParammovingAVG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParammovingAVG*>(ptr) != nullptr;
}

bool CParammovingAVG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

void CParammovingAVG::setParam(Length param) {
	m_param = param;
}

Length CParammovingAVG::getParam() const {
	return m_param;
}

END_MAVER_EMG_NAMESPACE
