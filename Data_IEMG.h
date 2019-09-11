//CData_IEMG object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_IEMG_DATA_H
#define _MAVER_EMG_ALGO_IEMG_DATA_H
#include "data.h"
BEGIN_MAVER_EMG_NAMESPACE
class CData_IEMG :
	public CData
{
public:
	CData_IEMG();
	~CData_IEMG();
	CData_IEMG(const CData_IEMG& rhs);
	CData_IEMG(const std::string& classname);
	CData_IEMG& operator =(const CData_IEMG& rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_IEMG_DATA_H

