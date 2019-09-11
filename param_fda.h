#ifndef _MAVOR_EMG_PARAM_FDA_H_
#define _MAVOR_EMG_PARAM_FDA_H_

#include "param.h"
#include <string>
#include <vector>

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class CParamFDA : public CParam
{
public:
	CParamFDA();

	virtual ~CParamFDA();

	CParamFDA(const CParamFDA& rhs);

	CParamFDA(const std::string& class_name);

	CParamFDA& operator = (const CParamFDA& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	// -----------------------------------------------------------------------------------
	// 此类独有信息
	// -----------------------------------------------------------------------------------

public:
	bool		setParams(string type_in, float freq_in);
public:
	string	type;		//频域分析类型
	//	有效输入：
	//			平均频率MNF/平均频谱频率MSF/中心频率CF/平均功率频率MPF		eg:"MNF"
	//			中位频率 MF/MDF
	//			功率谱密度PSD
	//			频谱面积SPA
	float		freq;		//采样频率
};

END_MAVER_EMG_NAMESPACE
#endif