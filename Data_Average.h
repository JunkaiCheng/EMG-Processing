//Data_Average object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_AVERAGE_DATA_H
#define _MAVER_EMG_ALGO_AVERAGE_DATA_H
#include"data.h"
BEGIN_MAVER_EMG_NAMESPACE
class CData_Average :
	public CData
{
public:
	CData_Average();
	~CData_Average();
	CData_Average(const CData_Average& rhs);
	CData_Average(const std::string& classname);
	CData_Average& operator =(const CData_Average& rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void SetMeanList(const std::vector<float> temp);
	std::vector<float> GetMeanList();
private:
	std::vector<float> MeanList;
};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_AVERAGE_DATA_H

