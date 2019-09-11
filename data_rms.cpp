#include "data_rms.h"


BEGIN_MAVER_EMG_NAMESPACE


CDataRMSFilter::CDataRMSFilter() : CData("DataRMSFilter")
{
}


CDataRMSFilter::~CDataRMSFilter()
{
}

CDataRMSFilter::CDataRMSFilter(const CDataRMSFilter& rhs) : CData(rhs)
{
}

CDataRMSFilter::CDataRMSFilter(const std::string& classname) : CData(classname)
{
}

CDataRMSFilter& CDataRMSFilter::operator = (const CDataRMSFilter& rhs)
{
	setClassName(rhs.getClassName());
	CData::operator= (rhs);
	return *this;
}

CObject* CDataRMSFilter::clone() const
{
	return new CDataRMSFilter(*this);
}

bool CDataRMSFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataRMSFilter*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CDataRMSFilter::clone_shared() const
{
	return std::make_shared<CDataRMSFilter>(*this);
}

bool CDataRMSFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}


END_MAVER_EMG_NAMESPACE
