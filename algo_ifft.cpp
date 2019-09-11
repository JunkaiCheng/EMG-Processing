#include "algo_ifft.h"


#pragma comment (lib,"fftw/libfftw3-3.lib")
#pragma comment (lib,"fftw/libfftw3f-3.lib")
#pragma comment (lib,"fftw/libfftw3l-3.lib")
#include "fftw/fftw3.h"
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

CAlgoIFFT::CAlgoIFFT() : CAlgo("CAlgoIFFT")
{
	m_output = std::make_shared<CData>();
}

CAlgoIFFT::~CAlgoIFFT()
{}

CAlgoIFFT::CAlgoIFFT(const CAlgoIFFT& rhs) : CAlgo(rhs)
{
	CAlgoIFFT::operator=(rhs);
}

CAlgoIFFT::CAlgoIFFT(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CData>();
}

CAlgoIFFT& CAlgoIFFT::operator= (const CAlgoIFFT& rhs)
{
	CAlgo::operator= (rhs);
	//m_output = rhs.m_output;
	//m_input = rhs.m_input;

	// Ó¦¸ÃÓÃ deep copy :
	this->m_input = dynamic_pointer_cast<CDataFFT>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	return *this;
}

CObject* CAlgoIFFT::clone() const
{
	return new CAlgoIFFT(*this);
}

std::shared_ptr<CObject> CAlgoIFFT::clone_shared() const
{
	return std::make_shared<CAlgoIFFT>(*this);
}

bool CAlgoIFFT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoIFFT*>(ptr) != nullptr;
}

bool CAlgoIFFT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoIFFT::setInputData(std::shared_ptr<CData> input_data)
{
	if (std::dynamic_pointer_cast<CDataFFT, CData>(input_data) == nullptr)
		return false;

	m_input = std::dynamic_pointer_cast<CDataFFT, CData>(input_data);
	return true;
}

bool CAlgoIFFT::execute()
{
	if (m_input.use_count() == 0)
		return false;

	if (m_input->getOutputDataComplex().empty())
		return false;

	size_t channels = m_input->getOutputDataComplex().size();
	size_t datalength = m_input->getOutputDataComplex()[0].size();

	if (datalength <= 2)
		return false;

	for (size_t i = 0; i < channels; i++)
	{
		if (datalength != m_input->getOutputDataComplex()[i].size())
			return false;
	}

	m_output->resizeOutputData(channels);

	fftwf_complex* in;
	fftwf_complex* out;
	fftwf_plan p;

	in = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * datalength);
	out = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * datalength);

	for (size_t i = 0; i < channels; i++)
	{
		CDataSeriesCpx src_data;
		m_input->getDataSeriesComplex(i, src_data);

		CDataSeries out_data_series;
		out_data_series.resize(datalength);

		for (size_t j = 0; j < datalength; j++)
		{
			in[j][0] = src_data[j].real();
			in[j][1] = src_data[j].imag();
		}

		p = fftwf_plan_dft_1d(static_cast<int>(datalength), in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

		fftwf_execute(p);

		for (size_t j = 0; j < datalength; j++)
		{
			out_data_series[j] = out[j][0] / static_cast<float>(datalength);
		}

		fftwf_destroy_plan(p);

		m_output->setDataSeries(i, out_data_series);
	}

	fftw_free(in);
	fftw_free(out);

	return true;
}

std::shared_ptr<CData> CAlgoIFFT::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE