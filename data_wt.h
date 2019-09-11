//WT data class by yuanjian 2019-4-9

#ifndef _MAVER_EMG_ALGO_DATA_WT_H_
#define _MAVER_EMG_ALGO_DATA_WT_H_

#include "data.h"

BEGIN_MAVER_EMG_NAMESPACE

class CDataWT : public CData
{
public:
	CDataWT();

	~CDataWT();

	CDataWT(const CDataWT& rhs);

	CDataWT(const std::string& classname);

	CDataWT& operator = (const CDataWT& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

public:
	std::vector<std::vector<int>>& getLongs();

	bool getDataSeriesLongs(size_t idx, std::vector<int>&data_series);

	void setLongs(std::vector<std::vector<int>>& new_longs);

	void resizeLongs(size_t resize_datasize);

	bool setDataSeriesLongs(size_t idx, std::vector<int>&data_series);

	//void setType(string &s);

	//string& getType();

private:
	std::vector<std::vector<int>>  longs;

	//std::string		type; //ÂË²¨Æ÷µÄÀàÐÍ
};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_DATA_WT_H_


