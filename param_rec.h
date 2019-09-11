//Parameter class for rectifier by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_REC_PARAM_FFT_H_
#define _MAVER_EMG_REC_PARAM_FFT_H_

#include "param.h"


BEGIN_MAVER_EMG_NAMESPACE

typedef char RecParam;
// Parameter for Rectifier:
// 'h': half-wave rectifier
// 'f': full-wave rectifier

class CParamRectifier : public CParam
{
public:
	CParamRectifier();
	~CParamRectifier();

	CParamRectifier(const CParamRectifier& rhs);

	CParamRectifier(const std::string& class_name);

	CParamRectifier& operator = (const CParamRectifier& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	void setParam(RecParam param);

	RecParam getParam() const;

private:
	RecParam m_param = 'f';
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_REC_PARAM_H_
