// by yuanjian 2019-4-10

#ifndef _MAVER_EMG_ALGO_PARAM_WT_FILTER_H_
#define _MAVER_EMG_ALGO_PARAM_WT_FILTER_H_

#include "param.h"
#include <string>
using std::string;

BEGIN_MAVER_EMG_NAMESPACE

class CParamWtFilter : public CParam
{
public:
	CParamWtFilter();

	virtual ~CParamWtFilter();

	CParamWtFilter(const CParamWtFilter& rhs);

	CParamWtFilter(const std::string& class_name);

	CParamWtFilter& operator = (const CParamWtFilter& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	/* -- 此类特有: --*/
public:
	bool	setValue(string TPTR_in, string SORH_in, string SCAL_in, int N_in, string wname_in);
	//private:
public:
	string		TPTR;		//TPTR — Threshold selection rule
		// 有效输入 :  
		// "sqtwolog" "minimaxi" "rigrsure" "heursure"

	string		SORH;		//SORH — Type of thresholding
		// 有效输入 :  
		// “s”"h"

	string		SCAL;		//SCAL — Multiplicative threshold rescaling
		// 有效输入 :  
		// “one”"sln" "mln"

	int			N;				//N — Level of wavelet decomposition
		// N>0

	string		wname;	//wname — Name of wavelet
		// 有效输入 :
		// sym1-45 db1-45 coif1-5 fk4 6 8 14 18 22
};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_