//Algorithm class for RMSFilter by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_RMS_ALGO_H_
#define _MAVER_EMG_RMS_ALGO_H_

#include "algorithm.h"
#include "data_rms.h"
#include "param_rms.h"


BEGIN_MAVER_EMG_NAMESPACE

class CAlgoRMSFilter : public CAlgo
{
public:
	CAlgoRMSFilter();
	~CAlgoRMSFilter();

	CAlgoRMSFilter(const CAlgoRMSFilter& rhs);

	CAlgoRMSFilter(const std::string& class_name);

	CAlgoRMSFilter& operator = (const CAlgoRMSFilter& rhs);

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
	std::shared_ptr<CParamRMSFilter>	m_param;
	std::shared_ptr<CDataRMSFilter>		m_output;
	std::shared_ptr<CData>				m_input;

};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_RMS_ALGO_H_