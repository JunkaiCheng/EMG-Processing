//CParam_FratcalDim object by hebaoxiang 2019-04-22
#ifndef _MAVER_EMG_ALGO_FRACTALDIM_PARAMETER_H
#define _MAVER_EMG_ALGO_FRACTALDIM_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_FractalDim : public CParam
{
public:
	CParam_FractalDim();
	~CParam_FractalDim();

	CParam_FractalDim(const CParam_FractalDim& rhs);

	CParam_FractalDim(const std::string& class_name);

	CParam_FractalDim& operator = (const CParam_FractalDim& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void SetParam(float temp_ratio,int temp_log_size);
	float GetRatio();
	int Get_log_size();

private:
	float ratio;//С��1���ó�ԭ���ݵ�ǰ�ٷ�֮100*ratio������ѡȡ���ʵ�ʱ���ӳ٣�
	int log_size;//��������ͼ�ĵ���
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_FRACTALDIM_PARAMETER_H

