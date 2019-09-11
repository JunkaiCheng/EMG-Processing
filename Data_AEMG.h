//CData_AEMG object by hebaoxiang 2019-04-08
#ifndef _MAVER_EMG_ALGO_AEMG_DATA_H
#define _MAVER_EMG_ALGO_AEMG_DATA_H
#include"data.h"
BEGIN_MAVER_EMG_NAMESPACE
class CData_AEMG :
	public CData
{
public:
	CData_AEMG();
	~CData_AEMG();
	CData_AEMG(const CData_AEMG& rhs);
	CData_AEMG(const std::string& classname);
	CData_AEMG& operator =(const CData_AEMG& rhs);
public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void SetAEMG(const CDataSeries& temp);
	CDataSeries GetAEMG();
	void SetRMS(const CDataSeries& temp);
	CDataSeries GetRMS();
	void SetMSD(const CDataSeries& temp);
	CDataSeries GetMSD();
	void SetCrossZeroRate(const CDataSeries& temp);
	CDataSeries GetCrossZeroRate();
	void SetMaxVal(const CDataSeries& temp);
	CDataSeries GetMaxVal();
private:
	CDataSeries AEMG;
	CDataSeries RMS;
	CDataSeries MSD;
	CDataSeries CrossZeroRate;
	CDataSeries MaxVal;
};

END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_AEMG_DATA_H

