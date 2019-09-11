// CAlgo_IEMG object by hebaoxiang 2019-04-06
#ifndef _MAVER_EMG_ALGO_IEMG_ALGORITHM_H
#define _MAVER_EMG_ALGO_IEMG_ALGORITHM_H
#include "algorithm.h"
#include "Param_IEMG.h"
#include "Data_IEMG.h"
BEGIN_MAVER_EMG_NAMESPACE
class CAlgo_IEMG :
	public CAlgo
{
public:
	CAlgo_IEMG();

	virtual ~CAlgo_IEMG();

	CAlgo_IEMG(const  CAlgo_IEMG& rhs);

	CAlgo_IEMG(const std::string& class_name);

	CAlgo_IEMG& operator = (const  CAlgo_IEMG& rhs);

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
	std::shared_ptr<CParam_IEMG>         m_param;
	std::shared_ptr<CData_IEMG>		    m_output;
	std::shared_ptr<CData>				m_input;

};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_IEMG_ALGORITHM_H
