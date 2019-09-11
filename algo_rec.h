//Algorithm class for rectifier by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_REC_ALGO_H_
#define _MAVER_EMG_REC_ALGO_H_

#include "algorithm.h"
#include "data_rec.h"
#include "param_rec.h"


BEGIN_MAVER_EMG_NAMESPACE

class CAlgoRectifier : public CAlgo
{
public:
	CAlgoRectifier();
	~CAlgoRectifier();

	CAlgoRectifier(const CAlgoRectifier& rhs);

	CAlgoRectifier(const std::string& class_name);

	CAlgoRectifier& operator = (const CAlgoRectifier& rhs);

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
	std::shared_ptr<CParamRectifier>	m_param;
	std::shared_ptr<CDataRectifier>		m_output;
	std::shared_ptr<CData>				m_input;

};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_REC_ALGO_H_