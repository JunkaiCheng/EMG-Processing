//Data class for movingAVG by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_MOVINGAVG_DATA_H_
#define _MAVER_EMG_MOVINGAVG_DATA_H_

#include "data.h"


BEGIN_MAVER_EMG_NAMESPACE

class CDatamovingAVG : public CData
{
public:
	CDatamovingAVG();
	~CDatamovingAVG();

	CDatamovingAVG(const CDatamovingAVG& rhs);

	CDatamovingAVG(const std::string& classname);

	CDatamovingAVG& operator = (const CDatamovingAVG& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_MOVINGAVG_DATA_H_
