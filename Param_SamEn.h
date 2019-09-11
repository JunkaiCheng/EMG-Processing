//CParam_SAmEn object by hebaoxiang 2019-04-11
#ifndef _MAVER_EMG_ALGO_SANEN_PARAMETER_H
#define _MAVER_EMG_ALGO_SANEN_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_SamEn : public CParam
{
public:
	CParam_SamEn();
	~CParam_SamEn();

	CParam_SamEn(const CParam_SamEn& rhs);

	CParam_SamEn(const std::string& class_name);

	CParam_SamEn& operator = (const CParam_SamEn& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	int GetEnDim();
	float GetTolerance();
	void SetEnDim(int temp);
	void SetTolerance(float temp);

private:
	int EnDim;
	float Tolerance;
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_SAMEN_PARAMETER_H




