/* data of starttime recog param by Junwei Deng*/

#ifndef __MAVER_EMG_ALGO_EMG_TIME_DATA_H
#define __MAVER_EMG_ALGO_EMG_TIME_DATA_H

#include "object.h"
#include "data.h"

BEGIN_MAVER_EMG_NAMESPACE

class CDataTimeRecog : public CData
{
public:
	CDataTimeRecog();

	virtual ~CDataTimeRecog();

	CDataTimeRecog(const CDataTimeRecog& rhs);

	CDataTimeRecog(const std::string &classname);

	CDataTimeRecog& operator = (const CDataTimeRecog& rhs);

public:
	CObject* clone() const;

	std::shared_ptr<CObject> clone_shared() const;

	bool isSameKindAs(const CObject* ptr);

	bool isSameKindAs(const std::shared_ptr<CObject> ptr);


private:
	std::vector<CDataSeries>	m_outputData;
};

END_MAVER_EMG_NAMESPACE
#endif
