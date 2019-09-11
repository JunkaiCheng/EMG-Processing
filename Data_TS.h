//DATA_TS object by hebaoxiang 2019-04-07
#ifndef _MAVER_EMG_ALGO_TS_DATA_H
#define _MAVER_EMG_ALGO_TS_DATA_H
#include "data.h"
BEGIN_MAVER_EMG_NAMESPACE
class CData_TS :
	public CData
{
public:
	CData_TS();
	~CData_TS();
	CData_TS(const CData_TS& rhs);
	CData_TS(const std::string& classname);
	CData_TS& operator =(const CData_TS& rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_TS_DATA_H
