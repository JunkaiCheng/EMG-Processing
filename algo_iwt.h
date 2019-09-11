#ifndef _MAVOR_EMG_IWT_ALGO_H_
#define _MAVOR_EMG_IWT_ALGO_H_
#include "algorithm.h"
#include "data_wt.h"
#include "param_wt.h"
#include "dwt.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoIWT : public CAlgo
{
public:
	CAlgoIWT();
	~CAlgoIWT();
	CAlgoIWT(const CAlgoIWT& rhs);
	CAlgoIWT(const std::string& class_name);
	CAlgoIWT& operator = (const CAlgoIWT& rhs);
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
	std::shared_ptr<CParamWT>		param;
	std::shared_ptr<CData>				m_output;
	std::shared_ptr<CDataWT>			m_input;
public:
	DWT			dwt;
};

END_MAVER_EMG_NAMESPACE
#endif	//_MAVOR_EMG_IWT_ALGO_H_