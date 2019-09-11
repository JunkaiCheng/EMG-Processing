//CParam_RenyiEn object by hebaoxiang 2019-04-12
#ifndef _MAVER_EMG_ALGO_RENYIEN_PARAMETER_H
#define _MAVER_EMG_ALGO_RENYIEN_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_RenyiEn : public CParam
{
public:
	CParam_RenyiEn();
	~CParam_RenyiEn();

	CParam_RenyiEn(const CParam_RenyiEn& rhs);

	CParam_RenyiEn(const std::string& class_name);

	CParam_RenyiEn& operator = (const CParam_RenyiEn& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void SetSubSectionNum(int temp);
	int GetSubSectionNum();
	void SetOrder(float temp);
	float GetOrder();

private:
	int SubSectionNum;//序列个数
	float Order;//次数
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_RENYIEN_PARAMETER_H

