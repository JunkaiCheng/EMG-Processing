//CAlgo_FractalDim object by hebaoxiang 2019-04-16
#ifndef _MAVER_EMG_ALGO_FRATCAL_DIM_ALGORITHM_H
#define _MAVER_EMG_ALGO_FRATCAL_DIM_ALGORITHM_H
#include "algorithm.h"
#include "Param_FractalDim.h"
#include"my_INTERPOLATION.h"
#include"Estimate_TimeInterval.h"
#include "Data_FractalDim.h"
BEGIN_MAVER_EMG_NAMESPACE
class CAlgo_FractalDim :
	public CAlgo
{
public:
	CAlgo_FractalDim();

	virtual ~CAlgo_FractalDim();

	CAlgo_FractalDim(const  CAlgo_FractalDim& rhs);

	CAlgo_FractalDim(const std::string& class_name);

	CAlgo_FractalDim& operator = (const  CAlgo_FractalDim& rhs);

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
	std::shared_ptr<CParam_FractalDim> m_param;
	std::shared_ptr<CData_FractalDim>  m_output;
	std::shared_ptr<CData>				m_input;

};
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ALGO_FRATCAL_DIM_ALGORITHM_H
