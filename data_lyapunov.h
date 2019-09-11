//Data class for Lyapunov by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_LYAPUNOV_DATA_H_
#define _MAVER_EMG_LYAPUNOV_DATA_H_

#include "data.h"


BEGIN_MAVER_EMG_NAMESPACE

typedef float LyaExp;

class CDataLyapunov : public CData
{
public:
	CDataLyapunov();
	~CDataLyapunov();

	CDataLyapunov(const CDataLyapunov& rhs);

	CDataLyapunov(const std::string& classname);

	CDataLyapunov& operator = (const CDataLyapunov& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	//get all of output data
	std::vector<LyaExp>& getOutputData();

	//get single data series, if idx is greater than m_outputData.size(), return false
	bool getDataSeries(size_t idx, LyaExp& data_series);

	//set all of output data
	void setOutputData(std::vector<LyaExp>& output_data);

	//resize output data, if you use setOutputData() function, don't call this function
	void resizeOutputData(size_t resize_datasize);

	//set data series, you must first alloc memory using resizeOutputData() function
	bool setDataSeries(size_t idx, LyaExp data_series);

private:
	std::vector<LyaExp>	m_outputData;

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_LYAPUNOV_DATA_H_
