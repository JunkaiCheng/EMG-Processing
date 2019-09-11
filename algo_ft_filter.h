#ifndef _MAVOR_EMG_FT_FILTER_ALGO_H_
#define _MAVOR_EMG_FT_FILTER_ALGO_H_
#include "algorithm.h"
#include "data_fft.h"
#include "param_ft_filter.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoFtFilter : public CAlgo
{
public:
	CAlgoFtFilter();
	~CAlgoFtFilter();
	CAlgoFtFilter(const CAlgoFtFilter& rhs);
	CAlgoFtFilter(const std::string& class_name);
	CAlgoFtFilter& operator = (const CAlgoFtFilter& rhs);
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
	std::shared_ptr<CParamFtFilter>		param;
	std::shared_ptr<CData>						m_output;
	std::shared_ptr<CData>						m_input;
};

END_MAVER_EMG_NAMESPACE
#endif	//_MAVOR_EMG_FT_FILTER_ALGO_H_