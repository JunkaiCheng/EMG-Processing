//data object by maanbang 2019-3-31

#ifndef _MAVER_EMG_ALGO_DATA_H_
#define _MAVER_EMG_ALGO_DATA_H_

#include "object.h"
#include <vector>

BEGIN_MAVER_EMG_NAMESPACE

typedef std::vector<float> CDataSeries;

class CData : public CObject
{
public:
	CData();

	virtual ~CData();

	CData(const CData& rhs);

	CData(const std::string& classname);

	CData& operator = (const CData& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	//get all of output data
	std::vector<CDataSeries>& getOutputData();

	//get single data series, if idx is greater than m_outputData.size(), return false
	bool getDataSeries(size_t idx, CDataSeries& data_series);

	//set all of output data
	void setOutputData(std::vector<CDataSeries>& output_data);

	//resize output data, if you use setOutputData() function, don't call this function
	void resizeOutputData(size_t resize_datasize);

	//set data series, you must first alloc memory using resizeOutputData() function
	bool setDataSeries(size_t idx, CDataSeries& data_series);

private:
	std::vector<CDataSeries>	m_outputData;

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_DATA_H_
