//Algorithm class for Lyapunov by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_LYAPUNOV_ALGO_H_
#define _MAVER_EMG_LYAPUNOV_ALGO_H_

#include "algorithm.h"
#include "data_Lyapunov.h"
#include "param_Lyapunov.h"


BEGIN_MAVER_EMG_NAMESPACE

class CAlgoLyapunov : public CAlgo
{
public:
	CAlgoLyapunov();
	~CAlgoLyapunov();

	CAlgoLyapunov(const CAlgoLyapunov& rhs);

	CAlgoLyapunov(const std::string& class_name);    

	CAlgoLyapunov& operator = (const CAlgoLyapunov& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	virtual bool setParam(std::shared_ptr<CParam> input_param);

	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

private:
	std::shared_ptr<CParamLyapunov>	    m_param;
	std::shared_ptr<CDataLyapunov>		m_output;
	std::shared_ptr<CData>				m_input;
	
	int calculateTau(CDataSeries& data_series);
	int calculateD();
	LyaExp calculateLya();
	float euclideanDist(int tau, CDataSeries& data_series, int m, int k, int l);
	int nearestNeighbor(int tau, CDataSeries& data_series, int i, int d);
	float shortestDistance(int tau, CDataSeries& data_series, int i, int d);
	int detE(int tau, CDataSeries& data_series);
	int ranE(int tau, CDataSeries& data_series);

};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_LYAPUNOV_ALGO_H_