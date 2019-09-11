#ifndef _MAVER_EMG_ALGO_AEMG_ALGORITHM_H
#define _MAVER_EMG_ALGO_AEMG_ALGORITHM_H
#include "algorithm.h"
#include "Param_AEMG.h"
#include "Data_AEMG.h"
BEGIN_MAVER_EMG_NAMESPACE
class CAlgo_AEMG :
	public CAlgo
{
public:
	CAlgo_AEMG();

	virtual ~CAlgo_AEMG();

	CAlgo_AEMG(const  CAlgo_AEMG& rhs);

	CAlgo_AEMG(const std::string& class_name);

	CAlgo_AEMG& operator = (const  CAlgo_AEMG& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	virtual bool setParam(std::shared_ptr<CParam> input_param);

	virtual bool execute();
	bool execute_RMS();
	bool execute_MSD();
	bool execute_CrossZeroRate();
	bool execute_MaxVal();

	virtual std::shared_ptr<CData> getOutputData();
private:
	std::shared_ptr<CParam_AEMG>         m_param;
	std::shared_ptr<CData_AEMG>		    m_output;
	std::shared_ptr<CData>				m_input;

};
END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_AEMG_ALGORITHM_H


