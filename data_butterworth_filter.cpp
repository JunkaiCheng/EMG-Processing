
#include "data_butterworth_filter.h"
#include <iostream>

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

CDataButterworthFilter::CDataButterworthFilter(): CData("CDataButterworthFilter")
{
}

CDataButterworthFilter::~CDataButterworthFilter()
{
}

CDataButterworthFilter::CDataButterworthFilter(const CDataButterworthFilter& rhs): CData(rhs)
{
	CDataButterworthFilter::operator=(rhs);
}

CDataButterworthFilter::CDataButterworthFilter(const std::string& classname): CData(classname)
{
}

CDataButterworthFilter& CDataButterworthFilter::operator = (const CDataButterworthFilter& rhs)
{
	CData::operator=(rhs);
	return *this;
}

CObject* CDataButterworthFilter::clone() const
{
	return new CDataButterworthFilter(*this);
}

std::shared_ptr<CObject> CDataButterworthFilter::clone_shared() const
{
	return std::make_shared<CDataButterworthFilter>(*this);
}

bool CDataButterworthFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataButterworthFilter*>(ptr) != nullptr;
}

bool CDataButterworthFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}


END_MAVER_EMG_NAMESPACE

