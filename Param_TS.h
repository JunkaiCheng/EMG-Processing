//Param_TS object by hebaoxiang 2019-04-07
#ifndef _MAVER_EMG_ALGO_TS_PARAMETER_H
#define _MAVER_EMG_ALGO_TS_PARAMETER_H
#include "param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_TS :
	public CParam
{
public:
	CParam_TS();
	~CParam_TS();

	CParam_TS(const CParam_TS& rhs);

	CParam_TS(const std::string& class_name);

	CParam_TS& operator = (const CParam_TS& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void   Set_dstLength(int value);
	int  Get_dstLength();
private:
	int dst_length;
};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_TS_PARAMETER_H
