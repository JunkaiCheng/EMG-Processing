//Data class for rectifier by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_REC_DATA_H_
#define _MAVER_EMG_REC_DATA_H_

#include "data.h"


BEGIN_MAVER_EMG_NAMESPACE

class CDataRectifier : public CData
{
public:
	CDataRectifier();
	~CDataRectifier();

	CDataRectifier(const CDataRectifier& rhs);

	CDataRectifier(const std::string& classname);

	CDataRectifier& operator = (const CDataRectifier& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_REC_DATA_H_
