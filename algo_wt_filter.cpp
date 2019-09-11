// by yuanjian 2019-4-11
#include "algo_wt_filter.h"
#include "algo_wt.h"
#include "algo_iwt.h"
#include <iostream>
#include <algorithm>
//test
#include <fstream>

using namespace std;
#define    PI	3.141592653

BEGIN_MAVER_EMG_NAMESPACE

CAlgoWtFilter::CAlgoWtFilter() : CAlgo("CAlgoWtFilter")
{
	m_output = std::make_shared<CData>();
}

CAlgoWtFilter::~CAlgoWtFilter()
{
}

CAlgoWtFilter::CAlgoWtFilter(const CAlgoWtFilter& rhs) : CAlgo(rhs)
{
	CAlgoWtFilter::operator=(rhs);
}

CAlgoWtFilter::CAlgoWtFilter(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CData>();
}

CAlgoWtFilter& CAlgoWtFilter::operator = (const CAlgoWtFilter& rhs)
{
	CAlgo::operator=(rhs);
	this->m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	this->param = dynamic_pointer_cast<CParamWtFilter>(rhs.param->clone_shared());
	return *this;
}

CObject* CAlgoWtFilter::clone() const
{
	return new CAlgoWtFilter(*this);
}

std::shared_ptr<CObject> CAlgoWtFilter::clone_shared() const
{
	return std::make_shared<CAlgoWtFilter>(*this);
}

bool CAlgoWtFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoWtFilter*>(ptr) != nullptr;
}

bool CAlgoWtFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoWtFilter::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoWtFilter::setParam(std::shared_ptr<CParam> input_param)
{
	if (dynamic_cast<CParamWtFilter*>(input_param.get()) == nullptr) return false;
	param = dynamic_pointer_cast<CParamWtFilter>(input_param);
	return true;
}

std::shared_ptr<CData> CAlgoWtFilter::getOutputData()
{
	return m_output;
}

// -- EXECUTE --

#ifdef _DEBUG
inline static
void print_vec(vector<float> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}
inline static
void print_vec(vector<int> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}
#endif //!_DEBUG

void CAlgoWtFilter::wnoisest(std::vector<float>& result, std::vector<float> &c, std::vector<int> &l)
{
	vector<float>	det_coef;
	int level = l.size() - 2;
	result.resize(level);
	for (size_t i = 1; i <= level; i++)
	{
		dwt.detcoef(det_coef, c, l, i);
		result[i - 1] = median_abs(det_coef) / 0.6745f;
	}	
}
void CAlgoWtFilter::cumsum(std::vector<float> &result, std::vector<float> &x) {
	int length = x.size();		if (length == 0) return;
	result[0] = x[0];
	for (size_t i = 1; i < length; i++)
	{
		result[i] = result[i - 1] + x[i];
	}
}
float CAlgoWtFilter::norm(std::vector<float> &x) {
	int		n				= x.size();
	float		sq_sum	= 0;
	for (size_t i = 0; i < n; i++) {
		sq_sum += x[i] * x[i];
	}
	return sqrtf(sq_sum);
}
float CAlgoWtFilter::thselect(vector<float> &x, string tptr) {
	if (tptr == "rigrsure") {
		vector<float> sx2;						sx2.resize(x.size());
		vector<float> sx2_cumsum;		sx2_cumsum.resize(x.size());
		vector<float> risks;						risks.resize(x.size());

		for (size_t i = 0; i < x.size(); i++)
		{
			sx2[i] = x[i] * x[i];
		}
		sort(sx2.begin(), sx2.end());
		cumsum(sx2_cumsum, sx2);
		int min_risk_index = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			risks[i]	=	(		x.size() - 2 - 2 * float(i)		)/x.size()
						+	(		sx2_cumsum[i]					)/x.size()
						+	(		(x.size()-1-i)*sx2[i]			)/x.size();
			if (risks[i] < risks[min_risk_index])	min_risk_index = i;
		}

	#ifdef _DEBUG
		//print_vec(risks);
	#endif // _DEBUG

		return sqrtf(sx2[min_risk_index]);
	}

	if (tptr == "heursure") {
		int		n = x.size();
		float		hthr	= sqrtf(2 * logf(n + 0.0f));
		float		eta	= (powf(norm(x),2)-n)/n;
		float		crit	= powf((logf(n) / logf(2)) ,1.5) / sqrtf(n);
		if (eta < crit) {
			return hthr;
		}
		return min<float>(thselect(x,"rigrsure"), hthr);
	}

	if (tptr == "sqtwolog") {
		int		n = x.size();
		return	sqrtf(2 * logf(n + 0.0f));
	}

	if (tptr == "minimaxi") {
		int		n = x.size();
		if (n <= 32) {
			return 0;
		}
		return 0.3936f + 0.1829f*(logf(n) / logf(2));
	}

	return 0;
}
float CAlgoWtFilter::median_abs(std::vector<float> &x) {
	int n = x.size();					if (n == 0) return -1;
	vector<float> x_copy;		x_copy.resize(n);
	for (int i = 0; i < n; i++) {
		x_copy[i] = fabs(x[i]);
	}
	sort(x_copy.begin(), x_copy.end());
	if (n % 2 == 0)	return (x_copy[n / 2] + x_copy[n / 2 - 1]) / 2;
	return x_copy[n / 2];
}

inline static void  write_out(vector<vector<float>>&data, string filename, int channel, int length) {
	ofstream fout(filename);
	for (int i = 0; i < channel; i++) {
		for (int j = 0; j < length; j++) {
			fout << data[i][j] << " ";
		} fout << endl;
	}
	fout.close();
}

bool CAlgoWtFilter::execute() {
#ifdef _DEBUG
	cout << endl << "Use WTFT" << endl;
	cout << "TPTR:	" << param->TPTR << endl;
	cout << "SORH:	" << param->SORH << endl;
	cout << "SCAL:	" << param->SCAL << endl;
	cout << "Level:	" << param->N << endl;
	cout << "wname:	" << param->wname << endl << endl;
#endif //!_DEBUG

	if (param->TPTR != "rigrsure"	&& param->TPTR != "heursure" &&
		param->TPTR != "sqtwolog" && param->TPTR != "minimaxi")
		return false;
	if (param->SORH != "s" && param->SORH!= "h")
		return false;
	if (param->SCAL!= "one"&& param->SCAL!= "sln" && param->SCAL!= "mln")
		return false;
	if (param->N <= 0)
		return false;

	// wt - wavedec
	shared_ptr<CParamWT> param1_sp = shared_ptr<CParamWT>(new CParamWT);
	param1_sp->setValue(param->wname, param->N); //level>0
	shared_ptr<CAlgo> wt_sp = make_shared<CAlgoWT>();
	wt_sp->setParam(param1_sp);
	wt_sp->setInputData(m_input);
	wt_sp->execute();

	shared_ptr<CDataWT> filter_in_sp = dynamic_pointer_cast<CDataWT>(wt_sp->getOutputData());
	shared_ptr<CDataWT> filter_out_sp = make_shared<CDataWT>();
	// filter
	vector<CDataSeries>		&vec_in_c	= filter_in_sp->getOutputData();
	vector<vector<int>>		&vec_in_l		=  filter_in_sp->getLongs();
	vector<CDataSeries>		&vec_out_c	= filter_out_sp->getOutputData();
	vector<vector<int>>		&vec_out_l	= filter_out_sp->getLongs();

	int channel_num		= vec_in_c.size();
	int datalength			= vec_in_c[0].size();
	int level = param->N;
	vec_out_c.resize(channel_num);
	vec_out_l = vec_in_l;

	vector<float>		scal_vec;
	scal_vec.resize(datalength);

	for (int i = 0; i < channel_num; i++) {
		vec_out_c[i].resize(datalength);
		vec_out_c[i] = vec_in_c[i];
		/* -- 比较粗暴的滤波 ：除了最低频 approx coef 全变0再逆回去*/
		//for (int k = vec_out_l[i][0]; k < datalength; k++) {
		//	vec_out_c[i][k] = 0;
		//}

		/* -- 阈值滤波 */
		{
			vector<float> s;
			wnoisest(s, vec_in_c[i], vec_in_l[i]);
		
			if (param->SCAL == "one") {
				s = vector<float>(s.size(), 1);
			}
			if (param->SCAL == "sln") {
				s = vector<float>(s.size(), s[0]);
			}

			vector<int>		first;		first.resize(level);
			vector<int>		last;		last.resize(level);		//matlab index

			first[level - 1] = vec_in_l[i][0] + 1;
			last[level - 1] = vec_in_l[i][0] + 1 + vec_in_l[i][1] - 1;
			for (size_t k = 1; k < level; k++) { // 计算first last
				first[level - k - 1] = vec_in_l[i][k] + first[level - k];
				last[level - k - 1] = first[level - k - 1] + vec_in_l[i][k + 1] - 1;
			}

			for (size_t k = 1; k <= level; k++) {
				float thr  = 0;
				if (param->TPTR == "sqtwolog" || param->TPTR == "minimaxi") {
					thr = thselect(vec_in_c[i], param->TPTR);
				}	
				if (param->TPTR == "rigrsure" || param->TPTR == "heursure") {
					vector<float> seg;		seg.resize(vec_out_l[i][level - k + 1]);
					for (int j = first[k - 1] - 1; j <= last[k - 1] - 1; j++) {
						seg[j - (first[k - 1] - 1)] = vec_in_c[i][j] / s[k - 1];
					}
					thr = thselect(seg, param->TPTR);
				}

				thr *= s[k - 1];
				#ifdef _DEBUG
						cout << k << " " << thr << endl;
				#endif

				for (int j = first[k - 1] - 1; j <= last[k - 1] - 1; j++) {
					if (param->SORH == "h")
						if (fabs(vec_out_c[i][j]) <= thr) vec_out_c[i][j] = 0;
					if (param->SORH == "s") {
						float tmp = fabs(vec_out_c[i][j]);
						tmp = tmp - thr;
						tmp = (tmp + fabs(tmp)) / 2;
						vec_out_c[i][j] = (vec_out_c[i][j] > 0) ? tmp : (-tmp);
					}
				}
			} // for (size_t k = 1; k <= level; k++)

		}


	}// for (int i = 0; i < channel_num; i++)

	// iwt
	shared_ptr<CParamWT> param2_sp = shared_ptr<CParamWT>(new CParamWT);
	param2_sp->setValue(param->wname, 0); //level=0
	shared_ptr<CAlgo> iwt_sp = make_shared<CAlgoIWT>();
	iwt_sp->setParam(param2_sp);
	iwt_sp->setInputData(filter_out_sp);
	iwt_sp->execute();

	*(m_output) = *(iwt_sp->getOutputData());
	return true;
}

END_MAVER_EMG_NAMESPACE
