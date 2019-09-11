//Data class for RMSFilter by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_RMS_DATA_H_
#define _MAVER_EMG_RMS_DATA_H_

#include "data.h"


BEGIN_MAVER_EMG_NAMESPACE

class CDataRMSFilter : public CData
{
public:
	CDataRMSFilter();
	~CDataRMSFilter();

	CDataRMSFilter(const CDataRMSFilter& rhs);

	CDataRMSFilter(const std::string& classname);

	CDataRMSFilter& operator = (const CDataRMSFilter& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_RMS_DATA_H_
