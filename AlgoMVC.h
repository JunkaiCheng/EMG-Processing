//MVC(幅度标准化） object by hebaoxiang 2019-4-02

#ifndef _MAVER_EMG_ALGO_MVC_ALGORIGHM_H_
#define _MAVER_EMG_ALGO_MVC_ALGORIGHM_H_

#include "algorithm.h"
#include "data_MVC.h"
#include "Param_MVC.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoMVC : public CAlgo
{
public:
	CAlgoMVC();

	virtual ~CAlgoMVC();

	CAlgoMVC(const  CAlgoMVC& rhs);

	CAlgoMVC(const std::string& class_name);

	CAlgoMVC& operator = (const  CAlgoMVC& rhs);

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
	std::shared_ptr<CParam_MVC>         m_param;
	std::shared_ptr<CData_MVC>		    m_output;
	std::shared_ptr<CData>				m_input;

};

END_MAVER_EMG_NAMESPACE

#endif // !
