
#ifndef _MAVOR_EMG_ALGO_FDA_
#define _MAVOR_EMG_ALGO_FDA_

#include "algorithm.h"
#include "data_fda.h"
#include "param_fda.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoFDA : public CAlgo
{
public:
	CAlgoFDA();

	~CAlgoFDA();

	CAlgoFDA(const CAlgoFDA& rhs);

	CAlgoFDA(const std::string& class_name);

	CAlgoFDA& operator = (const CAlgoFDA& rhs);

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
	std::shared_ptr<CParamFDA>				param;
	std::shared_ptr<CData>							m_input;
	std::shared_ptr<CDataFDA>					m_output;

};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVOR_EMG_ALGO_FDA_
