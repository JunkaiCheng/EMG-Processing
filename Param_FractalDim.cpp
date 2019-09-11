#include "Param_FractalDim.h"
BEGIN_MAVER_EMG_NAMESPACE


CParam_FractalDim::CParam_FractalDim() :CParam("CParam_FractalDim")
{
}


CParam_FractalDim::~CParam_FractalDim()
{
}

CParam_FractalDim::CParam_FractalDim(const CParam_FractalDim& rhs)
{
	CParam_FractalDim::operator=(rhs);
}
CParam_FractalDim::CParam_FractalDim(const std::string& class_name)
{
	CParam::CParam(class_name);
}

CParam_FractalDim& CParam_FractalDim::operator= (const CParam_FractalDim& rhs)
{
	CParam::operator=(rhs);
	ratio = rhs.ratio;
	log_size = rhs.log_size;
	return *this;
}

CObject* CParam_FractalDim::clone() const
{
	return new CParam_FractalDim(*this);
}

std::shared_ptr<CObject> CParam_FractalDim::clone_shared() const
{
	return std::make_shared<CParam>(*this);
}

bool CParam_FractalDim::isSameKindAs(const CObject* ptr)
{
	bool temp = dynamic_cast<const CParam_FractalDim*>(ptr) != nullptr;
	return temp;
}

bool CParam_FractalDim::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}
void CParam_FractalDim::SetParam(float temp_ratio, int temp_log_size)
{
	ratio = temp_ratio;
	log_size = temp_log_size;
}
float CParam_FractalDim::GetRatio()
{
	return ratio;
}
int CParam_FractalDim::Get_log_size()
{
	return log_size;
}

END_MAVER_EMG_NAMESPACE

