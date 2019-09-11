//param object by maanbang 2019-3-31

#ifndef _MAVER_EMG_ALGO_PARAM_H_
#define _MAVER_EMG_ALGO_PARAM_H_

#include "object.h"

BEGIN_MAVER_EMG_NAMESPACE

class CParam : public CObject
{
public:
	CParam();

	virtual ~CParam();

	CParam(const CParam& rhs);

	CParam(const std::string& class_name);

	CParam& operator = (const CParam& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_
