
#ifndef _MAVER_EMG_ALGO_PARAM_FT_FILTER_H_
#define _MAVER_EMG_ALGO_PARAM_FT_FILTER_H_

#include "param.h"
#include <string>
using std::string;

BEGIN_MAVER_EMG_NAMESPACE

class CParamFtFilter : public CParam
{
public:
	CParamFtFilter();   

	virtual ~CParamFtFilter();

	CParamFtFilter(const CParamFtFilter& rhs);

	CParamFtFilter(const std::string& class_name);

	CParamFtFilter& operator = (const CParamFtFilter& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

/* -- ��������: --*/
public:
	bool	setValue(string type, float low, float high);
//private:
public:
	string	Type;	//true:ͨ[Low,High] false:��[Low,High]
	float		High;	//[0,1]֮�� 1��ʾ����Ƶ�ʵ�һ��
	float		Low;		//[0,1]֮�� 1��ʾ����Ƶ�ʵ�һ��
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_
