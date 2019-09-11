//CAlgo_SamEn object by hebaoxiang 2019-04-11
#ifndef _MAVER_EMG_ALGO_SamEn_ALGORITHM_H
#define _MAVER_EMG_ALGO_SamEn_ALGORITHM_H
#include "algorithm.h"
#include "Data_SamEn.h"
#include "Param_SamEn.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgo_SamEn : public CAlgo
{
public:
	CAlgo_SamEn();

	virtual ~CAlgo_SamEn();

	CAlgo_SamEn(const  CAlgo_SamEn& rhs);

	CAlgo_SamEn(const std::string& class_name);

	CAlgo_SamEn& operator = (const  CAlgo_SamEn& rhs);

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
	std::shared_ptr<CParam_SamEn>         m_param;
	std::shared_ptr<CData_SamEn>		    m_output;
	std::shared_ptr<CData>				m_input;

};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_SamEn_ALGORITHM_H


