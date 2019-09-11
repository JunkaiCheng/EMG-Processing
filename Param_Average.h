//CParam_Average object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_AVERAGE_PARAMETER_H
#define _MAVER_EMG_ALGO_AVERAGE_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_Average : public CParam
{
public:
	CParam_Average();
	~CParam_Average();

	CParam_Average(const CParam_Average& rhs);

	CParam_Average(const std::string& class_name);

	CParam_Average& operator = (const CParam_Average& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void Set_dstLength(int value);
	int Get_dstLength();
private:
	int dst_length;
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_AVERAGE_PARAMETER_H



