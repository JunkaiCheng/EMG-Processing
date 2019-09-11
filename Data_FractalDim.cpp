#include "Data_FractalDim.h"

BEGIN_MAVER_EMG_NAMESPACE

CData_FractalDim::CData_FractalDim() :CData("CData_FractalDim")
{
}

CData_FractalDim::~CData_FractalDim()
{
}

CData_FractalDim::CData_FractalDim(const CData_FractalDim&rhs) :CData(rhs)
{
	DimList = rhs.DimList;

}

CData_FractalDim::CData_FractalDim(const std::string &classname) : CData(classname)
{

}

CData_FractalDim& CData_FractalDim::operator=(const CData_FractalDim& rhs)
{
	CData::operator=(rhs);
	DimList = rhs.DimList;
	return *this;
}

CObject* CData_FractalDim::clone() const
{
	return new CData_FractalDim(*this);
}

bool CData_FractalDim::isSameKindAs(const CObject *ptr)
{
	return dynamic_cast<const CData_FractalDim*>(ptr) != nullptr;
}

std::shared_ptr<CObject> CData_FractalDim::clone_shared() const
{
	return std::make_shared<CData_FractalDim>(*this);
}

bool CData_FractalDim::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CData_FractalDim::SetDimList(const std::vector<float> temp)
{
	DimList = temp;
}
std::vector<float> CData_FractalDim::GetDimList()
{
	return DimList;
}

END_MAVER_EMG_NAMESPACE