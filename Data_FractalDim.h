//CData_FratcalDim object by hebaoxiang 2019-04-16
#ifndef _MAVER_EMG_ALGO_FRACTALDIM_DATA_H
#define _MAVER_EMG_ALGO_FRACTALDIM_DATA_H
#include"data.h"
BEGIN_MAVER_EMG_NAMESPACE
class CData_FractalDim :
	public CData
{
public:
	CData_FractalDim();
	~CData_FractalDim();
	CData_FractalDim(const CData_FractalDim& rhs);
	CData_FractalDim(const std::string& classname);
	CData_FractalDim& operator =(const CData_FractalDim& rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void SetDimList(const std::vector<float> temp);
	std::vector<float> GetDimList();
private:
	std::vector<float> DimList;
};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_FRACTALDIM_DATA_H

