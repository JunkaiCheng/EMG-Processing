//CData_AEMG object by hebaoxiang 2019-0408
#ifndef _MAVER_EMG_ALGO_AEMG_PARAMETER_H
#define _MAVER_EMG_ALGO_AEMG_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_AEMG : public CParam
{
public:
	CParam_AEMG();
	~CParam_AEMG();

	CParam_AEMG(const CParam_AEMG& rhs);

	CParam_AEMG(const std::string& class_name);

	CParam_AEMG& operator = (const CParam_AEMG& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_AEMG_PARAMETER_H


