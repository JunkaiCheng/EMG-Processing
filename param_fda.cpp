// µ¼Èë¿â
#include <iostream>
#include "param_fda.h"

BEGIN_MAVER_EMG_NAMESPACE

CParamFDA::CParamFDA() : CParam("CParamFDA")
{

}

CParamFDA::~CParamFDA()
{
}

CParamFDA::CParamFDA(const CParamFDA& rhs) : CParam(rhs)
{
	CParamFDA::operator=(rhs);
}

CParamFDA::CParamFDA(const std::string& class_name) : CParam(class_name)
{

}

CParamFDA& CParamFDA::operator = (const CParamFDA& rhs)
{
	CParam::operator=(rhs);
	type = rhs.type;
	freq = rhs.freq;
	return *this;
}

CObject* CParamFDA::clone() const
{
	return new CParamFDA(*this);
}

std::shared_ptr<CObject> CParamFDA::clone_shared() const
{
	return std::make_shared<CParamFDA>(*this);
}

bool CParamFDA::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CParamFDA*>(ptr) != nullptr;
}

bool CParamFDA::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CParamFDA::setParams(string type_in, float freq_in)
{
	type = "";		
	if (type_in == "MNF" || type_in == "MSF" || type_in == "CF" || type_in == "MPF") {
		type = "MNF";
	}
	if (type_in == "MF" || type_in == "MDF" ) {
		type = "MDF";
	}
	if (type_in == "PSD") {
		type = "PSD";
	}
	if (type_in == "SPA") {
		type = "SPA";
	}
	freq = freq_in;
	return ((freq > 0) && type != "");
}

END_MAVER_EMG_NAMESPACE