/* data of starttime recog by Junwei Deng*/

#include "data_time_recog.h"
#include <iostream>
BEGIN_MAVER_EMG_NAMESPACE

CDataTimeRecog::CDataTimeRecog() : CData("Ctimerecog")
{}

CDataTimeRecog::~CDataTimeRecog()
{}

CDataTimeRecog::CDataTimeRecog(const CDataTimeRecog& rhs) : CData(rhs)
{}

CDataTimeRecog::CDataTimeRecog(const std::string& class_name) : CData(class_name)
{}

CDataTimeRecog& CDataTimeRecog::operator = (const CDataTimeRecog& rhs)
{
	setClassName(rhs.getClassName());
	return *this;
}

CObject* CDataTimeRecog::clone() const
{
	return new CDataTimeRecog(*this);
}

std::shared_ptr<CObject> CDataTimeRecog::clone_shared() const
{
	return std::make_shared<CDataTimeRecog>(*this);
}

bool  CDataTimeRecog::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CDataTimeRecog*>(ptr) != nullptr;
}

bool CDataTimeRecog::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}


END_MAVER_EMG_NAMESPACE