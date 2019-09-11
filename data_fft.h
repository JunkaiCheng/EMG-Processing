// FFt data class by yuanjian 2019-4-3
// revised by maanbang 2019-4-4

#ifndef _MAVER_EMG_ALGO_DATA_FFT_H_
#define _MAVER_EMG_ALGO_DATA_FFT_H_

#include "data.h"
#include <complex>

BEGIN_MAVER_EMG_NAMESPACE

typedef std::vector<std::complex<float>> CDataSeriesCpx;

class CDataFFT : public CData
{
public:
	CDataFFT();

	~CDataFFT();

	CDataFFT(const CDataFFT& rhs);
	
	CDataFFT(const std::string& classname);

	CDataFFT& operator = (const CDataFFT& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

public:
	std::vector<CDataSeriesCpx>& getOutputDataComplex();

	bool getDataSeriesComplex(size_t idx, CDataSeriesCpx& data_series);

	void setOutputDataComplex(std::vector<CDataSeriesCpx>& output_data);

	void resizeOutputDataComplex(size_t resize_datasize);

	bool setDataSeriesComplex(size_t idx, CDataSeriesCpx& data_series);

private:
	std::vector<CDataSeriesCpx>	m_outputDataComplex;
};

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_EMG_ALGO_DATA_FFT_H_

