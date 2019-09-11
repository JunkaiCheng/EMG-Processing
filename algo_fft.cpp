#include "algo_fft.h"

#pragma comment (lib,"fftw/libfftw3-3.lib")
#pragma comment (lib,"fftw/libfftw3f-3.lib")
#pragma comment (lib,"fftw/libfftw3l-3.lib")
#include "fftw/fftw3.h"
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

CAlgoFFT::CAlgoFFT() : CAlgo("CAlgoFFT")
{
	m_output = std::make_shared<CDataFFT>("CDataFFT");
}

CAlgoFFT::~CAlgoFFT()
{}

CAlgoFFT::CAlgoFFT(const CAlgoFFT& rhs) : CAlgo(rhs)
{
	CAlgoFFT::operator=(rhs);
}

CAlgoFFT::CAlgoFFT(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CDataFFT>("CDataFFT");
}

CAlgoFFT& CAlgoFFT::operator = (const CAlgoFFT& rhs)
{
	CAlgo::operator=(rhs);
	//m_output = rhs.m_output;
	//m_input = rhs.m_input;

	// Ó¦¸ÃÓÃ deep copy :
	this->m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CDataFFT>(rhs.m_output->clone_shared());
	return *this;
}

CObject* CAlgoFFT::clone() const
{
	return new CAlgoFFT(*this);
}

std::shared_ptr<CObject> CAlgoFFT::clone_shared() const
{
	return std::make_shared<CAlgoFFT>(*this);
}

bool CAlgoFFT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoFFT*>(ptr) != nullptr;
}

bool CAlgoFFT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoFFT::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

std::shared_ptr<CData> CAlgoFFT::getOutputData()
{
	return m_output;
}

bool CAlgoFFT::execute()
{
	if (m_input.use_count() == 0)
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	//step 1 check data
	//////////////////////////////////////////////////////////////////////////

	if (m_input->getOutputData().empty())
		return false;

	size_t channels = m_input->getOutputData().size();
	size_t datalength = m_input->getOutputData()[0].size();

	if (datalength <= 2)
		return false;

	for (size_t i = 1; i < channels; i++)
	{
		if (datalength != m_input->getOutputData()[i].size())
			return false;
	}

	//////////////////////////////////////////////////////////////////////////
	//// calc
	//////////////////////////////////////////////////////////////////////////
	
	m_output->resizeOutputDataComplex(channels);
	m_output->resizeOutputData(channels);
	
	fftwf_complex* in;
	fftwf_complex* out;
	fftwf_plan p;

	in = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * datalength);
	out = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * datalength);

	for (size_t i = 0; i < channels; i++)
	{
		//get data
		CDataSeries src_data;
		m_input->getDataSeries(i, src_data);

		

		CDataSeries out_data_abs;
		out_data_abs.resize(datalength);

		CDataSeriesCpx out_data_cpx;
		out_data_cpx.resize(datalength);

		for (size_t j = 0; j < datalength; j++)
		{
			in[j][0] = src_data[j];
			in[j][1] = 0.0;
		}

		p = fftwf_plan_dft_1d(static_cast<int>(datalength), in, out, FFTW_FORWARD, FFTW_ESTIMATE);

		fftwf_execute(p);

		for (size_t j = 0; j < datalength; j++)
		{
			out_data_cpx[j] = std::complex<float>(out[j][0], out[j][1]);
			out_data_abs[j] = std::abs(out_data_cpx[j]);
		}

		m_output->setDataSeriesComplex(i, out_data_cpx);
		m_output->setDataSeries(i, out_data_abs);

		fftwf_destroy_plan(p);

		
	}

	fftw_free(in);
	fftw_free(out);

	return true;
}

END_MAVER_EMG_NAMESPACE
