//Algorithm class for movingAVG by Junkai Cheng 04/01/2019

#ifndef _MAVER_EMG_MOVINGAVG_ALGO_H_
#define _MAVER_EMG_MOVINGAVG_ALGO_H_

#include "algorithm.h"
#include "data_movingAVG.h"
#include "param_movingAVG.h"


BEGIN_MAVER_EMG_NAMESPACE

class CAlgomovingAVG : public CAlgo
{
public:
	CAlgomovingAVG();
	~CAlgomovingAVG();

	CAlgomovingAVG(const CAlgomovingAVG& rhs);

	CAlgomovingAVG(const std::string& class_name);

	CAlgomovingAVG& operator = (const CAlgomovingAVG& rhs);

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
	std::shared_ptr<CParammovingAVG>	m_param;
	std::shared_ptr<CDatamovingAVG>		m_output;
	std::shared_ptr<CData>				m_input;

};


END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_MOVINGAVG_ALGO_H_