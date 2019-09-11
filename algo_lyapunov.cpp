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
// 计算时间延迟 tau

	int N = data_series.size(); //采样点数
	float initial = 0.0f;
	for (int i = 0; i < N; ++i) {
		initial += data_series[i] * data_series[i];
	}
	initial *= 1.0f / N; //自相关函数的初始值
	float threshold = initial * E;
	int t;
	for (t = 1; t < 100; ++t) {
		float temp = 0;
		for (int i = 0; i < N; ++i) {
			temp += data_series[i] * data_series[i + t];
		}
		temp *= 1.0f / N;
		if (temp - threshold < 0) //当自相关函数下降到初始值的 1 - 1/e 时，得到最佳时间延迟
			break;
	}
	return t;
}

float CAlgoLyapunov::euclideanDist(int tau, CDataSeries& data_series, int m, int k, int l) {
// 计算两组时间序列的欧几里得距离 
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
// 求与已知时间序列的最近邻的欧几里得距离
// y_i(d) 是已知时间序列， 则y_n(d) 是 y_i(d)的最近邻
// 返回 y_i(d) 和 y_n(d) 的欧几里得距离

	int N = data_series.size(); //采样点数
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
	// 在欧几里得距离下，求与已知时间序列的最近邻
	// y_i(d) 是已知时间序列， y_n(d) 是 y_i(d)的最近邻
	// 返回 n

	int N = data_series.size(); //采样点数
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
// 假设系统为确定性系统，计算嵌入维数d

	int N = data_series.size(); //采样点数
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
// 假设系统为随机系统，计算嵌入维数d

	int N = data_series.size(); //采样点数
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
	int size = m_input->getOutputData().size(); //通道数量
	int freq = m_param->getParam(); //采样频率
	float T = 1.0f / freq; //样本周期

	m_output->resizeOutputData(size);

	for (int i = 0; i < size; ++i) {
		//对每一个通道计算李雅普诺夫指数
		std::shared_ptr<CDataSeries> temp = std::make_shared<CDataSeries>();
		if (m_input->getDataSeries(i, *temp)) {
			//计算时间延迟 tau
			int tau = calculateTau(*temp);

			//计算嵌入维度 d
			int d = detE(tau, *temp);  
			if (d == 9)
				d = ranE(tau, *temp);

			//计算李雅普诺夫指数
			LyaExp lya_temp;
			int N = temp->size(); //采样点数
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

			//最小二乘法计算斜率-->最大李雅普诺夫指数
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
   