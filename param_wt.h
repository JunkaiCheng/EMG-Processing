// WT param class by yuanjian 2019-4-9

#ifndef _MAVER_EMG_ALGO_PARAM_WT_H_
#define _MAVER_EMG_ALGO_PARAM_WT_H_

#include "param.h"
#include <string>
using std::string;

BEGIN_MAVER_EMG_NAMESPACE

class CParamWT : public CParam
{
public:
	CParamWT();

	virtual ~CParamWT();

	CParamWT(const CParamWT& rhs);

	CParamWT(const std::string& class_name);

	CParamWT& operator = (const CParamWT& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	/* -- 此类特有: --*/
public:
	void	setValue(string type, int level);
	//private:
public:
	string	type;  //滤波器种类
	int		level;  //分解阶数
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_
