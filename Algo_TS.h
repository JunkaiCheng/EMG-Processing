//TS 时间标准化 object by hebaoxiang 2019-04-07

#ifndef _MAVER_EMG_ALGO_TS_ALGORITHM_H
#define _MAVER_EMG_ALGO_TS_ALGORITHM_H
#include "algorithm.h"
#include "Param_TS.h"
#include "Data_TS.h"
BEGIN_MAVER_EMG_NAMESPACE
class CAlgo_TS :
	public CAlgo
{
public:
	CAlgo_TS();

	virtual ~CAlgo_TS();

	CAlgo_TS(const  CAlgo_TS& rhs);

	CAlgo_TS(const std::string& class_name);

	CAlgo_TS& operator = (const  CAlgo_TS& rhs);

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
	std::shared_ptr<CParam_TS>         m_param;
	std::shared_ptr<CData_TS>		    m_output;
	std::shared_ptr<CData>				m_input;

};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_TS_ALGORITHM_