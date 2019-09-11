//mvc data class b
#ifndef _MAVER_EMG_ALGO_MVC_DATA_H_
#define _MAVER_EMG_ALGO_MVC_DATA_H_
#include "data.h"

BEGIN_MAVER_EMG_NAMESPACE

class CData_MVC :
	public CData
{
public:
	CData_MVC();
	~CData_MVC();
	CData_MVC(const CData_MVC& rhs);
	CData_MVC(const std::string & classname);
	CData_MVC& operator =(const CData_MVC & rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
};
END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_DATA_H_

