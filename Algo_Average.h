//CAlgo_AVerage object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_AVERAGE_ALGORITHM_H
#define _MAVER_EMG_ALGO_AVERAGE_ALGORITHM_H
#include "algorithm.h"
#include "data_Average.h"
#include "Param_Average.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgo_Average : public CAlgo
{
public:
	CAlgo_Average();

	virtual ~CAlgo_Average();

	CAlgo_Average(const  CAlgo_Average& rhs);

	CAlgo_Average(const std::string& class_name);

	CAlgo_Average& operator = (const  CAlgo_Average& rhs);

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
	std::shared_ptr<CParam_Average>         m_param;
	std::shared_ptr<CData_Average>		    m_output;
	std::shared_ptr<CData>					m_input;

};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_AVERAGE_ALGORITHM_H

