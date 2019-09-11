
#ifndef _MAVOR_EMG_ALGO_BUTTERWORTH_FILTER_H_
#define _MAVOR_EMG_ALGO_BUTTERWORTH_FILTER_H_

#include "algorithm.h"
#include "data_butterworth_filter.h"
#include "param_butterworth_filter.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoButterworthFilter: public CAlgo
{
public:
	CAlgoButterworthFilter();

	~CAlgoButterworthFilter();

	CAlgoButterworthFilter(const CAlgoButterworthFilter& rhs);

	CAlgoButterworthFilter(const std::string& class_name);

	CAlgoButterworthFilter& operator = (const CAlgoButterworthFilter& rhs);

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
	std::shared_ptr<CParamButterworthFilter>		m_param;
	std::shared_ptr<CData>							m_input;
	std::shared_ptr<CDataButterworthFilter>			m_output;

};








END_MAVER_EMG_NAMESPACE

#endif // !_MAVOR_EMG_ALGO_BUTTERWORTH_FILTER_H_
