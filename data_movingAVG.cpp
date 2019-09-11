#include "data_movingAVG.h"


BEGIN_MAVER_EMG_NAMESPACE


CDatamovingAVG::CDatamovingAVG() : CData("DatamovingAVG")
{
}


CDatamovingAVG::~CDatamovingAVG()
{
}

CDatamovingAVG::CDatamovingAVG(const CDatamovingAVG& rhs) : CData(rhs)
{
}

CDatamovingAVG::CDatamovingAVG(const std::string& classname) : CData(classname)
{
}

CDatamovingAVG& CDatamovingAVG::operator = (const CDatamovingAVG& rhs)
{
	setClassName(rhs.getClassName());
	CData::operator = (rhs);
	return *this;  
}

CObject* CDatamovingAVG::clone() const
{
	return new CDatamovingAVG(*this);
}

bool CDatamovingAVG::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDatamovingAVG*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CDatamovingAVG::clone_shared() const
{
	return std::make_shared<CDatamovingAVG>(*this);
}

bool CDatamovingAVG::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}



END_MAVER_EMG_NAMESPACE
