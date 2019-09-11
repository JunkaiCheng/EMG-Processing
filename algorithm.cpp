//algo object by maanbang 2019-3-31
#include "algorithm.h"

BEGIN_MAVER_EMG_NAMESPACE

CAlgo::CAlgo() : CObject("Algo")
{}

CAlgo::~CAlgo()
{}

CAlgo::CAlgo(const CAlgo& rhs) : CObject(rhs)
{}

CAlgo::CAlgo(const std::string& class_name) : CObject(class_name)
{}

CAlgo& CAlgo::operator = (const CAlgo& rhs)
{
	setClassName(rhs.getClassName());
	return *this;
}

CObject* CAlgo::clone() const
{
	return new CAlgo(*this);
}

std::shared_ptr<CObject> CAlgo::clone_shared() const
{
	return std::make_shared<CAlgo>(*this);
}

bool CAlgo::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo*>(ptr) != nullptr;
}

bool CAlgo::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo::setInputData(std::shared_ptr<CData> input_data)
{
	return true;
}

bool CAlgo::setParam(std::shared_ptr<CParam> input_param)
{
	return true;
}

bool CAlgo::execute()
{
	return true;
}

std::shared_ptr<CData> CAlgo::getOutputData()
{
	return std::make_shared<CData>();
}


END_MAVER_EMG_NAMESPACE