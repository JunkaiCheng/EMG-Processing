//CParam_IEMG object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_IEMG_PARAMETER_H
#define _MAVER_EMG_ALGO_IEMG_PARAMETER_H
#include"param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_IEMG : public CParam
{
public:
	CParam_IEMG();
	~CParam_IEMG();

	CParam_IEMG(const CParam_IEMG& rhs);

	CParam_IEMG(const std::string& class_name);

	CParam_IEMG& operator = (const CParam_IEMG& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	int GetType();
	void SetIntMethod(std::string &temp);
	void SetIntValue(float temp);
	float GetIntValue();

private:
	std::string IntMethod;
	float       IntValue;
	int Type;
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_IEMG_PARAMETER_H


