#include"Estimate_TimeInterval.h"
#include<algorithm>
BEGIN_MAVER_EMG_NAMESPACE
//例如 src=[[3,12,24,15,5,74,23,54,31,23,64,75]; interval_num=5;可将src分为[0,10,25,50,75],bincounts=[2 5 1 3 1] ind=[1 2 2 2..]
void Histc(const CDataSeries& src, const CDataSeries& comp, int interval_num, std::vector<int> &bincounts, std::vector<int>&ind)
{
	auto maxposition = std::max_element(comp.begin(), comp.end());
	auto maxvalue = *maxposition;
	auto minposition = std::min_element(comp.begin(), comp.end());
	auto minvalue = *minposition;
	double sub_length = (maxvalue - minvalue) / interval_num;
	double start, end;
	bincounts.clear();
	ind.clear();
	bincounts.resize(interval_num,0);
	ind.resize(src.size());
	for (size_t i = 0; i < interval_num; i++)
	{
		start = minvalue + i*sub_length;
		end = minvalue + (i + 1)*sub_length;
		if (i == interval_num - 1)
			end += 1000;
		else if (i == 0)
			start += -1000;
		for (size_t j = 0; j < src.size(); j++)
		{
			if (src[j] >= start&&src[j] < end)
			{
				bincounts[i] += 1;
				ind[j] = i;
			}
		}

	}
}

float MutualInformation(std::vector<int>&bincounts_x, std::vector<int>&ind_x, std::vector<int>&bincounts_y, std::vector<int>&ind_y)
{
	CDataSeries pmf_x;
	CDataSeries pmf_y;
	int interval_num = bincounts_x.size();
	int list_length = ind_x.size();
	pmf_x.resize(interval_num);
	pmf_y.resize(interval_num);
	for (size_t i = 0; i < interval_num; i++)
	{
		pmf_x[i] = float(bincounts_x[i]) / list_length;
		pmf_y[i] = float(bincounts_y[i]) / list_length;
	}
	std::vector<CDataSeries> jointPmf;
	jointPmf.resize(interval_num);
	for (size_t i = 0; i < interval_num; i++)
		jointPmf[i].resize(interval_num, 0);
	for (size_t i = 0; i < list_length; i++)
	{
		jointPmf[ind_x[i]][ind_y[i]] += 1;
	}

	float Hx, Hy, Hxy;
	Hx = 0;
	Hy = 0;
	for (size_t i = 0; i < interval_num; i++)
	{
		Hx += -1 * pmf_x[i] * log2(pmf_x[i] + pow(2.2204, -16));
		Hy += -1 * pmf_y[i] * log2(pmf_y[i] + pow(2.2204, -16));
	}
	Hxy = 0;
	float x = 0;
	for (size_t i = 0; i < interval_num; i++)
	{
		for (size_t j = 0; j < interval_num; j++)
		{
			x = jointPmf[i][j] / list_length;
			Hxy += -1 * x*log2(x + pow(2.2204, -16));
		}
	}
	float MI = Hx + Hy - Hxy;
	float mi = MI / pow(Hx*Hy, 0.5);
	return mi;

}

int Get_TimeInterval(CDataSeries& src, int length)
{
	std::vector<int> ind_x;
	std ::vector<int> counts_x;
	std::vector<int> ind_y;
	std::vector<int> counts_y;
	float temp_val1 = 1;
	float temp_val2;
	CDataSeries x, y;
	for (size_t i = 0; i < length; i++)
	{
		x.push_back(src[i]);
	}
	for (int tau = 0; tau <31; tau++)
	{
		for (size_t i = 0; i < length; i++)
		{
			y.push_back(src[i + tau]);
		}

		Histc(x, x, 20, counts_x, ind_x);
		Histc(y, x, 20, counts_y, ind_y);
		y.clear();
		temp_val2 = MutualInformation(counts_x, ind_x, counts_y, ind_y);
		if (temp_val2 > temp_val1)
			return tau;
		else
			temp_val1 = temp_val2;
	}
	return -1;
}

float euclideanDist(int tau, CDataSeries& data_series, int m, int k, int l) {
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

float shortestDistance(int tau, CDataSeries& data_series, int i, int d) {
	// 求与已知时间序列的最近邻的欧几里得距离
	// y_i(d) 是已知时间序列， 则y_n(d) 是 y_i(d)的最近邻
	// 返回 y_i(d) 和 y_n(d) 的欧几里得距离

	int N = data_series.size(); //采样点数
	float min = 99999.9;
	for (int j = 0; j < N - d * tau; ++j) {
		float temp = euclideanDist(tau, data_series, d, i, j);
		if (temp == 0)
			continue;
		if (temp < min) {
			min = temp;
		}
	}
	return min;
}

int nearestNeighbor(int tau, CDataSeries& data_series, int i, int d) {
	// 在欧几里得距离下，求与已知时间序列的最近邻
	// y_i(d) 是已知时间序列， y_n(d) 是 y_i(d)的最近邻
	// 返回 n

	int N = data_series.size(); //采样点数
	int n = 0;
	float min = 99999.9;
	for (int j = 0; j < N - d * tau; ++j) {
		float temp = euclideanDist(tau, data_series, d, i, j);
		if (temp == 0)
			continue;
		if (temp < min) {
			n = j;
			min = temp;
		}
	}
	return n;
}

int detE(int tau, CDataSeries& data_series) {
	// 假设系统为确定性系统，计算嵌入维数d

	int N = data_series.size(); //采样点数
	int d;
	float E1 = 0.0f;
	for (d = 0; d < 10; ++d) {
		float temp = 0.0f;
		if (d != 0) {
			for (int i = 0; i < N - d*tau; ++i)
				temp += shortestDistance(tau, data_series, i, d + 1) / shortestDistance(tau, data_series, i, d);
			temp *= 1.0f / (N - d*tau);
			if (fabs(1 - E1 / temp) < 0.1)
				break;
		}
		E1 = temp;
	}
	return d;
}

int ranE(int tau, CDataSeries& data_series) {
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

END_MAVER_EMG_NAMESPACE

