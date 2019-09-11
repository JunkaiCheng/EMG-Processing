#include "algo_lyapunov.h"
#include <cmath>
#include <vector>

BEGIN_MAVER_EMG_NAMESPACE

#define E 2.71828

CAlgoLyapunov::CAlgoLyapunov() : CAlgo("AlgoLyapunov")
{
	m_param = std::make_shared<CParamLyapunov>("ParamLyapunov");
	m_output = std::make_shared<CDataLyapunov>("DataLyapunov");
}


CAlgoLyapunov::~CAlgoLyapunov()
{
}

CAlgoLyapunov::CAlgoLyapunov(const CAlgoLyapunov& rhs) : CAlgo(rhs)
{
	CAlgoLyapunov::operator=(rhs);
}

CAlgoLyapunov::CAlgoLyapunov(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParamLyapunov>("ParamLyapunov");
	m_output = std::make_shared<CDataLyapunov>("DataLyapunov");
}

CAlgoLyapunov& CAlgoLyapunov::operator = (const CAlgoLyapunov& rhs)
{
	CAlgo::operator=(rhs);
	m_input = rhs.m_input;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgoLyapunov::clone() const
{
	return new CAlgoLyapunov(*this);
}

std::shared_ptr<CObject> CAlgoLyapunov::clone_shared() const
{
	return std::make_shared<CAlgoLyapunov>(*this);
}

bool CAlgoLyapunov::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoLyapunov*>(ptr) != nullptr;
}

bool CAlgoLyapunov::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoLyapunov::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoLyapunov::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		const CParam* par = input_param.get();
		const CParamLyapunov* tmp = dynamic_cast<const CParamLyapunov*>(par);
		m_param = std::make_shared<CParamLyapunov>(*tmp);
		return true;
	}
	else
		return false;
}

int CAlgoLyapunov::calculateTau(CDataSeries& data_series) {
// ����ʱ���ӳ� tau

	int N = data_series.size(); //��������
	float initial = 0.0f;
	for (int i = 0; i < N; ++i) {
		initial += data_series[i] * data_series[i];
	}
	initial *= 1.0f / N; //����غ����ĳ�ʼֵ
	float threshold = initial * E;
	int t;
	for (t = 1; t < 100; ++t) {
		float temp = 0;
		for (int i = 0; i < N; ++i) {
			temp += data_series[i] * data_series[i + t];
		}
		temp *= 1.0f / N;
		if (temp - threshold < 0) //������غ����½�����ʼֵ�� 1 - 1/e ʱ���õ����ʱ���ӳ�
			break;
	}
	return t;
}

float CAlgoLyapunov::euclideanDist(int tau, CDataSeries& data_series, int m, int k, int l) {
// ��������ʱ�����е�ŷ����þ��� 
// ||y_k(m) - y_l(m)|| = max(|x_{k+j*tau} - x_{l+j*tau}|), where 0 <= j <= m-1

	float max = 0.0f;
	for (int j = 0; j < m; ++j) {
		float temp = fabs(data_series[k + j*tau] - data_series[l + j*tau]);
		if (temp > max)
			max = temp;
	}
	return max;
}

float CAlgoLyapunov::shortestDistance(int tau, CDataSeries& data_series, int i, int d) {
// ������֪ʱ�����е�����ڵ�ŷ����þ���
// y_i(d) ����֪ʱ�����У� ��y_n(d) �� y_i(d)�������
// ���� y_i(d) �� y_n(d) ��ŷ����þ���

	int N = data_series.size(); //��������
	float min;
	for (int j = 0; j < N - d * tau; ++j) {
		float temp = euclideanDist(tau, data_series, d, i, j);
		if (temp == 0)
			continue;
		if (j == 0)
			min = temp;
		else if (temp < min){
			min = temp;
		}
	}
	return min;
}

int CAlgoLyapunov::nearestNeighbor(int tau, CDataSeries& data_series, int i, int d) {
	// ��ŷ����þ����£�������֪ʱ�����е������
	// y_i(d) ����֪ʱ�����У� y_n(d) �� y_i(d)�������
	// ���� n

	int N = data_series.size(); //��������
	int n = 0;
	float min;
	for (int j = 0; j < N - d * tau; ++j) {
		float temp = euclideanDist(tau, data_series, d, i, j);
		if (temp == 0)
			continue;
		if (j == 0)
			min = temp;
		else if (temp < min) {
			n = j;
			min = temp;
		}
	}
	return n;
}

int CAlgoLyapunov::detE(int tau, CDataSeries& data_series) {
// ����ϵͳΪȷ����ϵͳ������Ƕ��ά��d

	int N = data_series.size(); //��������
	int d;
	float E1 = 0.0f;
	for (int d = 0; d < 10; ++d) {
		float temp = 0.0f;
		if (d != 0) {
			for (int i = 0; i < N - d*tau; ++i) 
				temp += shortestDistance(tau, data_series, i, d + 1) / shortestDistance(tau, data_series, i, d);
			temp *= (1.0f / N - d*tau);
			if (fabs(1 - E1 / temp) < 0.1)
				break;
		}
		E1 = temp;
	}
	return d;
}

int CAlgoLyapunov::ranE(int tau, CDataSeries& data_series) {
// ����ϵͳΪ���ϵͳ������Ƕ��ά��d

	int N = data_series.size(); //��������
	int d;
	float E1 = 0.0f;
	for (int d = 0; d < 10; ++d) {
		float temp = 0.0f;
		if (d != 0) {
			for (int i = 0; i < N - d*tau; ++i)
				temp += fabs(data_series[i + d*tau] - data_series[nearestNeighbor(tau, data_series, i, d) + d*tau]);
			temp *= (1.0f / N - d*tau);
			if (fabs(1 - E1 / temp) < 0.1)
				break;
		}
		E1 = temp;
	}
	return d;
}

bool CAlgoLyapunov::execute()
{
	int size = m_input->getOutputData().size(); //ͨ������
	int freq = m_param->getParam(); //����Ƶ��
	float T = 1.0f / freq; //��������

	m_output->resizeOutputData(size);

	for (int i = 0; i < size; ++i) {
		//��ÿһ��ͨ������������ŵ��ָ��
		std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
		if (m_input->getDataSeries(i, *temp)) {
			//����ʱ���ӳ� tau
			int tau = calculateTau(*temp);

			//����Ƕ��ά�� d
			int d = detE(tau, *temp);  
			if (d == 9)
				d = ranE(tau, *temp);

			//����������ŵ��ָ��
			LyaExp lya_temp;
			int N = temp->size(); //��������
			int M = N - (d - 1)*tau;
			float K = 100.0f;

			std::vector<float> p;
			p.resize(100);

			for (int k = 0; k < K; ++k) {
				float sum = 0.0f;
				int temp_N = N - (d - 1)*tau;
				for (int n = 0; n < temp_N; ++n) {
					sum += log(shortestDistance(tau, *temp, n + k, d) / shortestDistance(tau, *temp, n, d));
				}
				p[k] = sum / N / T;
			}

			//��С���˷�����б��-->���������ŵ��ָ��
			float xy = 0.0f;
			float x = 0.0f;
			float y = 0.0f;
			float x2 = 0.0f;
			for (int k = 0; k < K; ++k) {
				xy += p[k] * k;
				x += k;
				y += p[k];
				x2 += k * k;
			}
			lya_temp = (xy / K - (x / K) * (y / K)) / (x2 / K - (x / K) * x / K);

			if (!m_output->setDataSeries(i, lya_temp))
				return false;
		}
		else return false;   
	}
	return true;
}
   
std::shared_ptr<CData> CAlgoLyapunov::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE
   