//Parameter class for Lyapunov by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_LYAPUNOV_PARAM_H_
#define _MAVER_EMG_LYAPUNOV_PARAM_H_

#include "param.h"


BEGIN_MAVER_EMG_NAMESPACE

typedef int Frequency;
//Sampling Frequency 

class CParamLyapunov : public CParam
{
public:
	CParamLyapunov();
	~CParamLyapunov();

	CParamLyapunov(const CParamLyapunov& rhs);

	CParamLyapunov(const std::string& class_name);

	CParamLyapunov& operator = (const CParamLyapunov& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	void setParam(Frequency param);

	Frequency getParam() const;

private:
	Frequency m_param = 6;
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_LYAPUNOV_PARAM_H_
