
#ifndef _MAVOR_EMG_DATA_BUTTEROWRTH_FILTER_H_
#define _MAVOR_EMG_DATA_BUTTEROWRTH_FILTER_H_

#include "data.h"

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class CDataButterworthFilter: public CData{
public:
	CDataButterworthFilter();

	virtual ~CDataButterworthFilter();

	CDataButterworthFilter(const CDataButterworthFilter& rhs);

	CDataButterworthFilter(const std::string& classname);

	CDataButterworthFilter& operator = (const CDataButterworthFilter& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

};

END_MAVER_EMG_NAMESPACE


#endif // !_MAVOR_EMG_DATA_BUTTEROWRTH_FILTER_H_

