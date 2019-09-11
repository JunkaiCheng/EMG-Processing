#ifndef _MAVER_EMG_ALGO_ALGO_IFFT_H_
#define _MAVER_EMG_ALGO_ALGO_IFFT_H_

#include "data_fft.h"
#include "algorithm.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoIFFT : public CAlgo
{
public:
	CAlgoIFFT();

	~CAlgoIFFT();

	CAlgoIFFT(const CAlgoIFFT& rhs);

	CAlgoIFFT(const std::string& class_name);

	CAlgoIFFT& operator = (const CAlgoIFFT& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

private:
	std::shared_ptr<CData>				m_output;
	std::shared_ptr<CDataFFT>			m_input;

};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_ALGO_IFFT_H_
