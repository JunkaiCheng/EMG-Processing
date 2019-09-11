#include "object.h"

BEGIN_MAVER_EMG_NAMESPACE

CObject::CObject()
{
	m_className = "CObject";
}

CObject::CObject(const std::string& class_name) : m_className(class_name)
{

}

CObject::CObject(const CObject& rhs)
{
	m_className = rhs.m_className;
}

CObject& CObject::operator= (const CObject& rhs)
{
	m_className = rhs.m_className;
	return *this;
}

CObject::~CObject()
{}

void CObject::setClassName(const std::string& class_name)
{
	m_className = class_name;
}

std::string CObject::getClassName() const
{
	return m_className;
}

CObject* CObject::clone() const
{
	return new CObject(*this);
}

std::shared_ptr<CObject> CObject::clone_shared() const
{
	return std::make_shared<CObject>(*this);
}

bool CObject::isSameKindAs(const CObject* ptr)
{
	return true;
}

bool CObject::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

END_MAVER_EMG_NAMESPACE
