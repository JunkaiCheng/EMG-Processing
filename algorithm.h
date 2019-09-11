//algo object by maanbang 2019-3-31

#ifndef _MAVER_EMG_ALGO_ALGORIGHM_H_
#define _MAVER_EMG_ALGO_ALGORIGHM_H_

#include "object.h"
#include "data.h"
#include "param.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgo : public CObject
{
public:
	CAlgo();

	virtual ~CAlgo();

	CAlgo(const CAlgo& rhs);

	CAlgo(const std::string& class_name);

	CAlgo& operator = (const CAlgo& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	virtual bool setParam(std::shared_ptr<CParam> input_param);

	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

};

END_MAVER_EMG_NAMESPACE

#endif // !
