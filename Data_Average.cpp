#include "Data_Average.h"
BEGIN_MAVER_EMG_NAMESPACE

CData_Average::CData_Average() :CData("CData_Average")
{
}

CData_Average::~CData_Average()
{
}

CData_Average::CData_Average(const CData_Average&rhs) :CData(rhs)
{
	MeanList = rhs.MeanList;
	
}

CData_Average::CData_Average(const std::string &classname) : CData(classname)
{

}

CData_Average& CData_Average::operator=(const CData_Average& rhs)
{
	CData::operator=(rhs);
	MeanList = rhs.MeanList;
	return *this;
}

CObject* CData_Average::clone() const
{
	return new CData_Average(*this);
}

bool CData_Average::isSameKindAs(const CObject *ptr)
{
	return dynamic_cast<const CData_Average*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_Average::clone_shared() const
{
	return std::make_shared<CData_Average>(*this);
}

bool CData_Average::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CData_Average::SetMeanList(const std::vector<float> temp)
{
	MeanList = temp;
}
std::vector<float> CData_Average::GetMeanList()
{
	return MeanList;
}

END_MAVER_EMG_NAMESPACE