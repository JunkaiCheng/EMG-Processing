#include "algo_ft_filter.h"
#include "algo_fft.h"
#include "algo_ifft.h"
#include <iostream>
using namespace std;
#define    PI	3.141592653

BEGIN_MAVER_EMG_NAMESPACE

CAlgoFtFilter::CAlgoFtFilter() : CAlgo("CAlgoFtFilter")
{
	m_output = std::make_shared<CDataFFT>();
	//cout << m_output.get() << endl;
}

CAlgoFtFilter::~CAlgoFtFilter()
{
}

CAlgoFtFilter::CAlgoFtFilter(const CAlgoFtFilter& rhs) : CAlgo(rhs)
{
	CAlgoFtFilter::operator=(rhs);
}

CAlgoFtFilter::CAlgoFtFilter(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CDataFFT>();
}

CAlgoFtFilter& CAlgoFtFilter::operator = (const CAlgoFtFilter& rhs)
{
	CAlgo::operator=(rhs);
	this->m_input		= dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output	= dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	this->param		= dynamic_pointer_cast<CParamFtFilter>(rhs.param->clone_shared());
	return *this;
}

CObject* CAlgoFtFilter::clone() const
{
	return new CAlgoFtFilter(*this);
}

std::shared_ptr<CObject> CAlgoFtFilter::clone_shared() const
{
	return std::make_shared<CAlgoFtFilter>(*this);
}

bool CAlgoFtFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoFtFilter*>(ptr) != nullptr;
}

bool CAlgoFtFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoFtFilter::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoFtFilter::setParam(std::shared_ptr<CParam> input_param)
{
	if (dynamic_cast<CParamFtFilter*>(input_param.get()) == nullptr) return false;
	param = dynamic_pointer_cast<CParamFtFilter>(input_param);
	return true;
}

std::shared_ptr<CData> CAlgoFtFilter::getOutputData()
{
	return m_output;
}

// -- EXECUTE --

inline static
void print_vec(vector<float> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}
inline static
void print_vec(vector<complex<float>> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}

bool CAlgoFtFilter::execute() {
#ifdef _DEBUG
	cout << endl << "Use FT filter" << endl;
	cout << "Type: " << (param->Type) << endl;
	cout << "High: " << (param->High) << endl;
	cout << "Low: " << (param->Low) << endl << endl;
#endif // !DEBUG

	// fft
	shared_ptr<CAlgo> fft_sp = shared_ptr<CAlgo>(new CAlgoFFT);
	fft_sp->setInputData(m_input);
	fft_sp->execute();

	shared_ptr<CDataFFT> filter_in_sp = dynamic_pointer_cast<CDataFFT> (fft_sp->getOutputData());
	shared_ptr<CDataFFT> filter_out_sp = shared_ptr<CDataFFT>(new CDataFFT);
	// filter
	vector<CDataSeries>		&vec_in_abs = filter_in_sp->getOutputData();
	vector<CDataSeriesCpx>	&vec_in_cpx = filter_in_sp->getOutputDataComplex();
	vector<CDataSeries>		&vec_out_abs = filter_out_sp->getOutputData();
	vector<CDataSeriesCpx>	&vec_out_cpx = filter_out_sp->getOutputDataComplex();

	int channel_num = vec_in_abs.size();
	int N = vec_in_abs[0].size();
	vec_out_abs.resize(channel_num);
	vec_out_cpx.resize(channel_num);

	for (int i = 0; i < channel_num; i++) {
		vec_out_abs[i].resize(N);
		vec_out_cpx[i].resize(N);
		if (param->Type == "pass"){
			vec_out_abs[i][0] = (param->Low != 0) ? 0 : vec_in_abs[i][0];
			vec_out_cpx[i][0] = (param->Low != 0) ? 0 : vec_in_cpx[i][0];
		}
		if (param->Type == "block"){
			vec_out_abs[i][0] = (param->Low == 0) ? 0 : vec_in_abs[i][0];
			vec_out_cpx[i][0] = (param->Low == 0) ? 0 : vec_in_cpx[i][0];
		}
		for (int k = 1; k < N; k++) {
			int		distance = (k > N - k) ? (N - k) : k;
			float		ratio = (distance + 0.0f)/ ((N + 0.0f) / 2) + 0.0f;
			bool		accept = false;
			if (param->Type == "pass"){
				accept = (ratio >= param->Low && ratio <= param->High);
			}
			if (param->Type == "block"){
				accept = (ratio <= param->Low || ratio >= param->High);
			}
			vec_out_abs[i][k] = (accept) ? vec_in_abs[i][k] : 0;
			vec_out_cpx[i][k] = (accept) ? vec_in_cpx[i][k] : 0;
		}//for (int k = 0; k < N; k++)
	}//for (int i = 0; i < channel_num; i++)

	//ifft
	shared_ptr<CAlgo> ifft_sp = shared_ptr<CAlgo>(new CAlgoIFFT);
	ifft_sp->setInputData(filter_out_sp);
	ifft_sp->execute();
	
	*(m_output) = *(ifft_sp->getOutputData());
	//fft_sp.reset();
	//ifft_sp.reset();
	return true;
}

END_MAVER_EMG_NAMESPACE
