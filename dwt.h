#pragma once

#include <string>
#include <vector>
#include "object.h"
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class DWT{
private:
	//	variable
	int		lf;//滤波器长度
	vector<float>	Lo_D;
	vector<float>	Hi_D;
	vector<float>	Lo_R;
	vector<float>	Hi_R;

	//	function
	void	wextend(vector<float> &result, vector<float>const &src, int lenEXT, string type);
	void	conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter);
	void	conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter, string type);
	void	down_sample(vector<float> &dest, vector<float>const &src);			//降采样
	void	up_sample(vector<float> &dest, vector<float>const &src, int type);	//升采样
	void	wkeep(vector<float> &result, vector<float> const &sig, int len, string type);
	void	upsconv(vector<float> &result, vector<float> const &sig, vector<float>&filter);			//升采样后卷积

public:
	//	variable

	//  function
	DWT();
	~DWT();
	bool		set_filters(string wname);					//设置滤波器

	void		dwt(vector<float> &result_a, vector<float> &result_d, vector<float>const &sig);
	void		idwt(vector<float> &sig_rec, vector<float> const&in_a, vector<float> const&in_d);
	bool		wavedec(vector<float> &result_c, vector<int> &result_l, vector<float> sig, int n);	//多解析度decompose
	void		detcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n);	//提取n-level detail coefficients
	void		appcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n);	//提取n-level approximation coefficients
	void		waverec(vector<float> &result, vector<float> &in_c, vector<int> &in_l);		//reconstruction(wavedec的逆变换)

	void		print_filters();	//输出filter
};

END_MAVER_EMG_NAMESPACE