// by yuanjian 2019-4-10

#include "param_wt_filter.h"


BEGIN_MAVER_EMG_NAMESPACE

CParamWtFilter::CParamWtFilter() : CParam("Param")
{
	TPTR = "rigrsure";		SORH = "s";					SCAL = "mln";
	N = 1;							wname = "sym10";
}

CParamWtFilter::~CParamWtFilter()
{}

CParamWtFilter::CParamWtFilter(const CParamWtFilter& rhs) : CParam(rhs)
{
	TPTR = rhs.TPTR;			SORH = rhs.SORH;		SCAL = rhs.SCAL;
	N = rhs.N;					wname = rhs.wname;
}

CParamWtFilter::CParamWtFilter(const std::string& class_name) : CParam(class_name)
{
	TPTR = "rigrsure";		SORH = "s";					SCAL = "mln";
	N = 1;							wname = "sym10";
}

CParamWtFilter& CParamWtFilter::operator= (const CParamWtFilter& rhs)
{
	CParam::operator=(rhs);
	TPTR = rhs.TPTR;			SORH = rhs.SORH;		SCAL = rhs.SCAL;
	N = rhs.N;					wname = rhs.wname;
	return *this;
}

CObject* CParamWtFilter::clone() const
{
	return new CParamWtFilter(*this);
}

std::shared_ptr<CObject> CParamWtFilter::clone_shared() const
{
	return std::make_shared<CParamWtFilter>(*this);
}

bool CParamWtFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamWtFilter*>(ptr) != nullptr;
}

bool CParamWtFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CParamWtFilter::setValue(string TPTR_in, string SORH_in, string SCAL_in, int N_in, string wname_in){
	
	if (TPTR_in!="rigrsure"	&& TPTR_in != "heursure" && TPTR_in != "sqtwolog" && TPTR_in != "minimaxi")
		return false;
	if (SORH_in != "s" && SORH_in != "h")
		return false;
	if (SCAL_in!="one"&& SCAL_in!="sln" && SCAL_in!="mln")
		return false;
	if (N_in <= 0)
		return false;

	TPTR = TPTR_in;			SORH = SORH_in;			SCAL = SCAL_in;
	N = N_in;						wname = wname_in;
	return true;
}

END_MAVER_EMG_NAMESPACE