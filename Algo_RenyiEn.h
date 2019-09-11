#ifndef _MAVER_EMG_ALGO_RENYIEN_ALGORITHM_H
#define _MAVER_EMG_ALGO_RENYIEN_ALGORITHM_H
#include "algorithm.h"
#include "Param_RenyiEn.h"
#include "Data_SamEn.h"
BEGIN_MAVER_EMG_NAMESPACE
class CAlgo_RenyiEn :
	public CAlgo
{
public:
	CAlgo_RenyiEn();

	virtual ~CAlgo_RenyiEn();

	CAlgo_RenyiEn(const  CAlgo_RenyiEn& rhs);

	CAlgo_RenyiEn(const std::string& class_name);

	CAlgo_RenyiEn& operator = (const  CAlgo_RenyiEn& rhs);

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
	std::shared_ptr<CParam_RenyiEn>         m_param;
	std::shared_ptr<CData_SamEn>		    m_output;
	std::shared_ptr<CData>					m_input;

};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_RENYIEN_ALGORITHM_H

