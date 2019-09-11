//by yuanjian 2019-4-12

#ifndef _MAVER_EMG_DATA_FDA_H_
#define _MAVER_EMG_DATA_FDA_H_

#include "data.h"
#include <vector>

BEGIN_MAVER_EMG_NAMESPACE

typedef std::vector<float> CDataSeries;

class CDataFDA : public CData
{
public:
	CDataFDA();

	~CDataFDA();

	CDataFDA(const CDataFDA& rhs);

	CDataFDA(const std::string& classname);

	CDataFDA& operator = (const CDataFDA& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE

#endif //_MAVER_EMG_DATA_FDA_H_
