//CAlgo_ApEn objectby hebaoxiang 2019-04-18
#ifndef _MAVER_EMG_ALGO_APEN_ALGORITHM_H
#define _MAVER_EMG_ALGO_APEN_ALGORITHM_H
#include "algorithm.h"
#include "Data_SamEn.h"
#include "Param_SamEn.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgo_ApEn : public CAlgo
{
public:
	CAlgo_ApEn();

	virtual ~CAlgo_ApEn();

	CAlgo_ApEn(const  CAlgo_ApEn& rhs);

	CAlgo_ApEn(const std::string& class_name);

	CAlgo_ApEn& operator = (const  CAlgo_ApEn& rhs);

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
#endif // !_MAVER_EMG_ALGO_APEN_ALGORITHM_H
