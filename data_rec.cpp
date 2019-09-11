#include "data_rec.h"


BEGIN_MAVER_EMG_NAMESPACE


CDataRectifier::CDataRectifier() : CData("DataRectifier")
{
}


CDataRectifier::~CDataRectifier()
{
}

CDataRectifier::CDataRectifier(const CDataRectifier& rhs) : CData(rhs)
{
}

CDataRectifier::CDataRectifier(const std::string& classname) : CData(classname)
{
}

CDataRectifier& CDataRectifier::operator = (const CDataRectifier& rhs)
{
	setClassName(rhs.getClassName());
	CData::operator = (rhs);
	return *this;
}

CObject* CDataRectifier::clone() const
{
	return new CDataRectifier(*this);
}

bool CDataRectifier::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataRectifier*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CDataRectifier::clone_shared() const
{
	return std::make_shared<CDataRectifier>(*this);
}

bool CDataRectifier::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}



END_MAVER_EMG_NAMESPACE
