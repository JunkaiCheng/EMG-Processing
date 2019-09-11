#include "algo_fda.h"
#include "algo_fft.h"
#include <iostream>
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

CAlgoFDA::CAlgoFDA() : CAlgo("CAlgoFDA")
{
	m_output = std::make_shared<CDataFDA>("CDataFDA");
}

CAlgoFDA::~CAlgoFDA()
{}

CAlgoFDA::CAlgoFDA(const CAlgoFDA& rhs) : CAlgo(rhs)
{
	CAlgoFDA::operator=(rhs);
}

CAlgoFDA::CAlgoFDA(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CDataFDA>("CDataFDA");
}

CAlgoFDA& CAlgoFDA::operator = (const CAlgoFDA& rhs)
{
	CAlgo::operator=(rhs);
	this->m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CDataFDA>(rhs.m_output->clone_shared());
	return *this;
}

CObject* CAlgoFDA::clone() const
{
	return new CAlgoFDA(*this);
}

std::shared_ptr<CObject> CAlgoFDA::clone_shared() const
{
	return std::make_shared<CAlgoFDA>(*this);
}

bool CAlgoFDA::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoFDA*>(ptr) != nullptr;
}

bool CAlgoFDA::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoFDA::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoFDA::setParam(std::shared_ptr<CParam> input_param)
{
	if (dynamic_cast<CParamFDA*>(input_param.get()) == nullptr) return false;
	param = dynamic_pointer_cast<CParamFDA>(input_param);
	return false;
}

std::shared_ptr<CData> CAlgoFDA::getOutputData()
{
	return m_output;
}

// -- EXECUTE --

float  get_integrate_f_S_df(vector<float> &f, vector<float> &S, float delta_f,  int n){

	if (n > f.size() || n > S.size()) return -1;

	float integrate_f_S_df = 0;

	for (int i = 0; i < n; i++) {
		integrate_f_S_df += S[i] * f[i] * delta_f;
	}

	return integrate_f_S_df;
}

float  get_integrate_S_df(vector<float> &S, float delta_f, int n) {

	if (n > S.size()) return -1;

	float integrate_S_df = 0;

	for (int i = 0; i < n; i++) {
		integrate_S_df += S[i] * delta_f;
	}

	return integrate_S_df;
}

float  get_integrate_S_S_df(vector<float> &S, float delta_f, int n) {

	if (n > S.size()) return -1;

	float integrate_S_df = 0;

	for (int i = 0; i < n; i++) {
		integrate_S_df += S[i] * S[i] * delta_f;
	}

	return integrate_S_df;
}

bool CAlgoFDA::execute(){
#ifdef _DEBUG
	cout << endl;
	cout << "Freq Domain Analysis:	 " << param->type << endl;
	cout << "Sampling Freq: " << param->freq << endl << endl;
#endif

	if (param.use_count() == 0)			return false;
	if (m_input.use_count() == 0)		return false;

	// - step 1	fft
	shared_ptr<CAlgo> fft_sp = shared_ptr<CAlgo>(new CAlgoFFT);
	fft_sp->setInputData(m_input);
	fft_sp->execute();

	shared_ptr<CDataFFT>		fda_in_sp = dynamic_pointer_cast<CDataFFT> (fft_sp->getOutputData());
	vector<CDataSeries>			&vec_in_abs = fda_in_sp->getOutputData();
	vector<CDataSeriesCpx>	&vec_in_cpx =fda_in_sp->getOutputDataComplex();

	//	- step 2	º∆À„∆µ¬ ÷·
	vector<float>		freq_axis;
	size_t channels		=		vec_in_abs.size();
	m_output->resizeOutputData(channels);
	size_t datalength		=		vec_in_abs[0].size();
	freq_axis.resize(datalength);
	for (size_t i = 0; i < datalength; i++)
	{
		freq_axis[i] = (param->freq)*i / datalength;
	}
	float delta_f = (param->freq) / datalength;

	if (param->type == "MNF") {
		for (size_t i = 0; i < channels; i++) {

			float integrate_f_S_df = 0;
			float integrate_S_df = 0;

			for (size_t j = 0; j <= (datalength / 2); j++) {
				integrate_f_S_df += vec_in_abs[i][j] * freq_axis[j] * delta_f;
				integrate_S_df += vec_in_abs[i][j] * delta_f;
			}

			vector<float> mnf;		mnf.resize(1);	
			if (integrate_S_df == 0)  return false;
			mnf[0] = integrate_f_S_df / integrate_S_df;

			m_output->setDataSeries(i, mnf);
		}
		return true;
	}

	if (param->type == "MDF") {
		for (size_t i = 0; i < channels; i++) {
			int		nmax = (datalength / 2) ;
			int		n_right = nmax;
			int		n_left = 0;
			int		n = (n_right + n_left) / 2;

			float		mid = get_integrate_S_df(vec_in_abs[i], delta_f, nmax) / 2;
			
			while (n_right - n_left > 1) {
				if (get_integrate_S_df(vec_in_abs[i], delta_f, n) > mid) {
					n_right = n;
					n = (n_right + n_left) / 2;
				}
				else {
					n_left = n;
					n = (n_right + n_left) / 2;
				}
			}

			vector<float> mdf;		mdf.resize(1);
			
			mdf[0] = freq_axis[n];

			m_output->setDataSeries(i, mdf);
		}
		return true;
	}

	if (param->type == "PSD") {
		for (size_t i = 0; i < channels; i++) {
			vector<float> mdf;		mdf.resize(1);

			mdf[0] = get_integrate_S_S_df(vec_in_abs[i], delta_f, (datalength / 2) + 1);

			m_output->setDataSeries(i, mdf);
		}
		return true;
	}

	if (param->type == "SPA") {
		for (size_t i = 0; i < channels; i++) {
			vector<float> mdf;		mdf.resize(1);

			mdf[0] = get_integrate_S_df(vec_in_abs[i], delta_f, (datalength / 2) + 1);

			m_output->setDataSeries(i, mdf);
		}
		return true;
	}

	return true;
}

END_MAVER_EMG_NAMESPACE
