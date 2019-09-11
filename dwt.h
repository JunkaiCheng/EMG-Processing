#pragma once

#include <string>
#include <vector>
#include "object.h"
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class DWT{
private:
	//	variable
	int		lf;//�˲�������
	vector<float>	Lo_D;
	vector<float>	Hi_D;
	vector<float>	Lo_R;
	vector<float>	Hi_R;

	//	function
	void	wextend(vector<float> &result, vector<float>const &src, int lenEXT, string type);
	void	conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter);
	void	conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter, string type);
	void	down_sample(vector<float> &dest, vector<float>const &src);			//������
	void	up_sample(vector<float> &dest, vector<float>const &src, int type);	//������
	void	wkeep(vector<float> &result, vector<float> const &sig, int len, string type);
	void	upsconv(vector<float> &result, vector<float> const &sig, vector<float>&filter);			//����������

public:
	//	variable

	//  function
	DWT();
	~DWT();
	bool		set_filters(string wname);					//�����˲���

	void		dwt(vector<float> &result_a, vector<float> &result_d, vector<float>const &sig);
	void		idwt(vector<float> &sig_rec, vector<float> const&in_a, vector<float> const&in_d);
	bool		wavedec(vector<float> &result_c, vector<int> &result_l, vector<float> sig, int n);	//�������decompose
	void		detcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n);	//��ȡn-level detail coefficients
	void		appcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n);	//��ȡn-level approximation coefficients
	void		waverec(vector<float> &result, vector<float> &in_c, vector<int> &in_l);		//reconstruction(wavedec����任)

	void		print_filters();	//���filter
};

END_MAVER_EMG_NAMESPACE