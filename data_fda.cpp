#include "data_fda.h"

BEGIN_MAVER_EMG_NAMESPACE

CDataFDA::CDataFDA() : CData("CDataFDA")
{}

CDataFDA::~CDataFDA()
{}

CDataFDA::CDataFDA(const CDataFDA& rhs) : CData(rhs)
{
}

CDataFDA::CDataFDA(const std::string& classname) : CData(classname)
{}

CDataFDA& CDataFDA::operator= (const CDataFDA& rhs)
{
	CData::operator=(rhs);
	return *this;
}

CObject* CDataFDA::clone() const
{
	return new CDataFDA(*this);
}

std::shared_ptr<CObject> CDataFDA::clone_shared() const
{
	return std::make_shared<CDataFDA>(*this);
}

bool CDataFDA::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataFDA*>(ptr) != nullptr;
}

bool CDataFDA::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return std::dynamic_pointer_cast<const CDataFDA, const CObject>(ptr) != nullptr;
}



END_MAVER_EMG_NAMESPACE


