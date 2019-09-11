// by yuanjian 2019-4-9

#include "param_ft_filter.h"

BEGIN_MAVER_EMG_NAMESPACE

CParamFtFilter::CParamFtFilter() : CParam("Param")
{
	Type = "pass";	High = 1;	Low = 0;
}

CParamFtFilter::~CParamFtFilter()
{}

CParamFtFilter::CParamFtFilter(const CParamFtFilter& rhs) : CParam(rhs)
{
	Type = rhs.Type;	High = rhs.High;	Low = rhs.Low;
}

CParamFtFilter::CParamFtFilter(const std::string& class_name) : CParam(class_name)
{
	Type = "pass";	High = 1;	Low = 0;
}

CParamFtFilter& CParamFtFilter::operator= (const CParamFtFilter& rhs)
{
	CParam::operator=(rhs);
	Type = rhs.Type;	High = rhs.High;	Low = rhs.Low;
	return *this;
}

CObject* CParamFtFilter::clone() const
{
	return new CParamFtFilter(*this);
}

std::shared_ptr<CObject> CParamFtFilter::clone_shared() const
{
	return std::make_shared<CParamFtFilter>(*this);
}

bool CParamFtFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamFtFilter*>(ptr) != nullptr;
}

bool CParamFtFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CParamFtFilter::setValue(string type, float low, float high) {
	if (type != "pass"&& type != "block") return false;
	if (low >= high || high >= 1) return false;
	Type = type;	High = high;	Low = low;
	return true;
}

END_MAVER_EMG_NAMESPACE