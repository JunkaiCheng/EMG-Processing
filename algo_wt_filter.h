#ifndef _MAVOR_EMG_FT_FILTER_ALGO_H_
#define _MAVOR_EMG_FT_FILTER_ALGO_H_
#include "algorithm.h"
#include "data_wt.h"
#include "param_wt_filter.h"
#include "dwt.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoWtFilter : public CAlgo
{
public:
	CAlgoWtFilter();
	~CAlgoWtFilter();
	CAlgoWtFilter(const CAlgoWtFilter& rhs);
	CAlgoWtFilter(const std::string& class_name);
	CAlgoWtFilter& operator = (const CAlgoWtFilter& rhs);
//private:
public:
	void wnoisest(std::vector<float>&result, std::vector<float> &c, std::vector<int> &l);
	float thselect(std::vector<float> &x, string tptr);
	void cumsum(std::vector<float> &result, std::vector<float> &x);
	float norm(std::vector<float> &x);
	float median_abs(std::vector<float> &x);
public:
	virtual CObject* clone() const;
	virtual std::shared_ptr<CObject> clone_shared() const;
	virtual bool isSameKindAs(const CObject* ptr);
	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	virtual bool setInputData(std::shared_ptr<CData> input_data);
	virtual bool setParam(std::shared_ptr<CParam> input_param);
	virtual bool execute();
	virtual std::shared_ptr<CData> getOutputData();
private:
	std::shared_ptr<CParamWtFilter>		param;
	std::shared_ptr<CData>						m_output;
	std::shared_ptr<CData>						m_input;
	DWT			dwt;//不用于分解
};

END_MAVER_EMG_NAMESPACE
#endif	//_MAVOR_EMG_FT_FILTER_ALGO_H_