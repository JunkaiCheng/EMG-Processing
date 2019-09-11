#ifndef _MAVER_EMG_ALGO_ALGO_FFT_H_
#define _MAVER_EMG_ALGO_ALGO_FFT_H_

#include "data_fft.h"
#include "algorithm.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoFFT : public CAlgo
{
public:
	CAlgoFFT();

	~CAlgoFFT();
	
	CAlgoFFT(const CAlgoFFT& rhs);
	
	CAlgoFFT(const std::string& class_name);
	
	CAlgoFFT& operator = (const CAlgoFFT& rhs);

public:
	virtual CObject* clone() const;
	
	virtual std::shared_ptr<CObject> clone_shared() const;
	
	virtual bool isSameKindAs(const CObject* ptr);
	
	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	
	virtual bool setInputData(std::shared_ptr<CData> input_data);
	
	virtual bool execute();
	
	virtual std::shared_ptr<CData> getOutputData();

private:
	std::shared_ptr<CDataFFT>			m_output;
	std::shared_ptr<CData>					m_input;

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_ALGO_FFT_H_
