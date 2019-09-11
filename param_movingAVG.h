//Parameter class for movingAVG by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_MOVINGAVG_PARAM_FFT_H_
#define _MAVER_EMG_MOVINGAVG_PARAM_FFT_H_

#include "param.h"


BEGIN_MAVER_EMG_NAMESPACE

typedef int Length;
//length of window

class CParammovingAVG : public CParam
{
public:
	CParammovingAVG();
	~CParammovingAVG();

	CParammovingAVG(const CParammovingAVG& rhs);

	CParammovingAVG(const std::string& class_name);

	CParammovingAVG& operator = (const CParammovingAVG& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	void setParam(Length param);

	Length getParam() const;

private:
	Length m_param = 6;
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_MOVINGAVG_PARAM_H_
