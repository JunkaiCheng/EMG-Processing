#include "dwt.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace MaverEMG;

// test ���filters
void DWT::print_filters(){
	int row = 10;
	int n;
	cout << "Lo_D" << endl;
	n = Lo_D.size();
	for (int i = 0; i < n; i++){
		cout << Lo_D[i] << " ";
		if ((i + 1) % row == 0 || i == n - 1) cout << endl;
	}
	cout << "Hi_D" << endl;
	n = Hi_D.size();
	for (int i = 0; i < n; i++){
		cout << Hi_D[i] << " ";
		if ((i + 1) % row == 0 || i == n - 1) cout << endl;
	}
	cout << "Lo_R" << endl;
	n = Lo_R.size();
	for (int i = 0; i < n; i++){
		cout << Lo_R[i] << " ";
		if ((i + 1) % row == 0 || i == n - 1) cout << endl;
	}
	cout << "Hi_R" << endl;
	n = Lo_D.size();
	for (int i = 0; i < n; i++){
		cout << Hi_R[i] << " ";
		if ((i + 1) % row == 0 || i == n - 1) cout << endl;
	}
}

DWT::DWT(){

}
DWT::~DWT(){

}

bool DWT::set_filters(string wname) {
	//ifstream	ifile("D:\\Project\\Code\\DWT\\gen_data\\test.txt");
	ifstream		ifile("dwt_filters.txt");
	string		line, type = "";
	int			size;
	float			num;
	istringstream in_ss;
	if (getline(ifile, line)) in_ss.str(line); else { ifile.close(); return false; }
	in_ss >> type;
	while (type != wname) {
		for (int i = 0; i < 4; i++)if (!getline(ifile, line)) { ifile.close(); return false; }
		if (getline(ifile, line)) { in_ss.clear(); in_ss.str(line); } else { ifile.close(); return false; }
		in_ss >> type;
	}
	if (type != wname) {
	//	û�ҵ��˲���
		cout << "ERROR: DWT::set_filters(srting)	input filter not valid" << endl;
		ifile.close();	return false;
	}
	in_ss >> size;
	lf = size;
	Lo_D.resize(size);		Hi_D.resize(size);		Lo_R.resize(size);		Hi_R.resize(size);
	if (getline(ifile, line)) { in_ss.clear(); in_ss.str(line); }  else { ifile.close(); return false; }
	for (int i = 0; i < size; i++) in_ss >> Lo_D[i];
	if (getline(ifile, line)) { in_ss.clear(); in_ss.str(line); }  else { ifile.close(); return false; }
	for (int i = 0; i < size; i++) in_ss >> Hi_D[i];
	if (getline(ifile, line)) { in_ss.clear(); in_ss.str(line); }  else { ifile.close(); return false; }
	for (int i = 0; i < size; i++) in_ss >> Lo_R[i];
	if (getline(ifile, line)) { in_ss.clear(); in_ss.str(line); }  else { ifile.close(); return false; }
	for (int i = 0; i < size; i++) in_ss >> Hi_R[i];

	ifile.close();
	return true;
}

/*��չ�ź�
*	��չx [lx]->[lx+2*lenEXT] lenEXTһ��Ϊlf-1 �������result
*	��	type = "sym"	wextend([1,2,3,4,5], 3) ->[3,2,1,1,2,3,4,5,5,4,3]
*		type = "zero"	wextend([1,2,3,4,5], 3) ->[0,0,0,1,2,3,4,5,0,0,0]
*/
void DWT::wextend(vector<float> &result, vector<float>const &src, int lenEXT, string type){
	result.resize(2 * lenEXT + src.size());
	/* zero 0 ��չ */
	if (type == "zero"){
		memcpy(&result[lenEXT], &src[0], src.size()*sizeof(float));
		for (int i = 1; i <= lenEXT; i++){
			result[lenEXT - i] = 0;
			result[src.size() + lenEXT + i - 1] = 0;
		}
		return;
	}
	/* sym  �Գ���չ */
	if (type == "sym"){
		int l_idx = 0;					int l_step = 1;
		int r_idx = src.size() - 1;		int r_step = -1;
		memcpy(&result[lenEXT], &src[0], src.size()*sizeof(float));
		for (int i = 1; i <= lenEXT; i++){
			result[lenEXT - i] = src[l_idx];
			result[src.size() + lenEXT + i - 1] = src[r_idx];
			if (i%src.size() == 0){
				l_step = -l_step;
				r_step = -r_step;
			}
			else{
				l_idx = l_idx + l_step;
				r_idx = r_idx + r_step;
			}
		}
		return;
	}//if (type == "sym")
}

/*���(Ĭ��lid)
*	��������[lx + 2*(lf-1)],[lf] -> [lx + lf - 1]
*	��([1,2,3,4,5],[2,3],5,2)->[7,12,17,22]
*	result����Ϊ a_ext �� b_ext
*/
void DWT::conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter){
	int size_filter = filter.size();
	int size_sig = sig.size();
	if (size_filter > size_sig){
		cout << "ERROR: size_filter > size_sig in function DWT::conv" << endl;
		return;
	}
	result.resize(size_sig - size_filter + 1);
	for (int i = 0; i < size_sig - size_filter + 1; i++){
		result[i] = 0;
		for (int j = size_filter - 1; j >= 0; j--){
			result[i] += sig[i + size_filter - 1 - j] * filter[j];
		}
	}
}

/*���
*	type = "valid"
*		��������[ls],[lf] -> [ls - lf + 1]
*		��([1,2,3,4,5],[2,3])->[7,12,17,22]
*	type = "full"
*		��������[ls],[lf] -> [ls + lf - 1]
*		��([1,2,3,4,5],[2,3])->[2,7,12,17,22,15]
*/
void DWT::conv(vector<float> &result, vector<float> const &sig, vector<float> const &filter, string type){
	if (type == "valid"){
		int size_filter = filter.size();
		int size_sig = sig.size();
		if (size_filter > size_sig){
			cout << "ERROR: size_filter > size_sig in function DWT::conv with type valid" << endl;
			return;
		}

		result.resize(size_sig - size_filter + 1);
		for (int i = 0; i < size_sig - size_filter + 1; i++){
			result[i] = 0;
			for (int j = size_filter - 1; j >= 0; j--){
				result[i] += sig[i + size_filter - 1 - j] * filter[j];
			}
		}
		return;
	}//if (type == "valid")
	if (type == "full"){
		int size_filter = filter.size();
		int size_sig = sig.size();

		vector<float> sig_ext; // extend sig with type:"zero" lenEXT: size_filter - 1 
		wextend(sig_ext, sig, size_filter-1, "zero");
		int size_sig_ext = sig_ext.size();

		result.resize(size_sig_ext - size_filter + 1);
		for (int i = 0; i < size_sig_ext - size_filter + 1; i++){
			result[i] = 0;
			for (int j = size_filter - 1; j >= 0; j--){
				result[i] += sig_ext[i + size_filter - 1 - j] * filter[j];
			}
		}
		return;
	}//if (type == "full")
}

/*��ȡ��(down_sample)
*	dest[i] =  src[2*i]
*/
void DWT::down_sample(vector<float> &dest, vector<float>const &src){
	int m = int(src.size() / 2);
	dest.resize(m);
	for (int i = 0; i < m; i++){
		dest[i] = src[2 * i + 1];
	}
}

/*��ȡ��(up_sample)
*	src ���� len
*	type = 1 : ����0���߶���0		�� 1 2 3 4 5 -> 0 1 0 2 0 3 0 4 0 5 0 
*	type = 0 : ����0���߶���src		�� 1 2 3 4 5 -> 1 0 2 0 3 0 4 0 5
*/
void DWT::up_sample(vector<float> &dest, vector<float>const &src, int type){
	if (type == 1){
		dest.resize(2 * src.size() + 1);
		for (int i = 0; i < dest.size(); i++){
			dest[i] = (i % 2 == 0) ? 0 : src[(i - 1) / 2];
		}
	}
	if (type == 0){
		dest.resize(2 * src.size() - 1);
		for (int i = 0; i < dest.size(); i++){
			dest[i] = (i % 2 == 1) ? 0 : src[(i + 1) / 2];
		}
	}
}

/*�����źŵ�һ����
*	type = "l"	result = sig[0:len-1]
*	type = "r"	result = sig[len_sig - len + 1, len_sig]
*	type = "c"	result = sig[]
*/
void DWT::wkeep(vector<float> &result, vector<float> const &sig, int len, string type){
	int start = 0;
	result.resize(len);
	int len_sig = sig.size();
	if (type == "c"){
		start = int(len_sig / 2) - int(len / 2) - 1 * (len % 2 != len_sig % 2);
	}
	if (type == "l"){
		start = 0;
	}
	if (type == "r"){
		start = len_sig - len;
	}
	memcpy(&result[0], &sig[start], len*sizeof(float));
}

/*	�ȶ�sig			up_sample(type = "zero") ���Ϊsig_ups
*	�ٶ�sig_ups		conv(type = "full")���Ϊsig_conv
*	result ȡsig_conv�м� 2*lx-lf+2 ��Ԫ��
*/
void DWT::upsconv(vector<float> &result, vector<float> const& sig, vector<float>&filter){
	if (sig.size() == 0){
		cout << "ERROR: signal size = 0" << endl;
		return;
	}
	int s = 2 * sig.size() - filter.size() + 2;
	vector<float> sig_ups;		//upsample���signal�ź�
	up_sample(sig_ups, sig, 0);
	vector<float> sig_conv;		//�������ź�
	conv(sig_conv, sig_ups, filter, "full");
	wkeep(result, sig_conv, s, "c");
}

/*���� x(ԭʼ�ź�) ����approx��detail�ɷ�(a,d)
*	approx��Ƶcoefficient, detail��Ƶcoefficient
*	��չ�� x_ext ���� lx2 = lx + 2(lf - 1)
*	a_ext[lx2-lf+1]	d_ext[lx2-lf+1]
*	a,d �� a_ext,d_ext �� downsample
*		1.	�� lx-lf+1 Ϊ����	a d[(lx2 - lf + 1)/2]
*		2.	�� lx-lf+1 Ϊż��	a d[(lx2 - lf)/2]
*/
void DWT::dwt(vector<float> &result_a, vector<float> &result_d, vector<float>const &sig){
	vector<float> sig_ext;
	vector<float> result_a_ext;
	vector<float> result_d_ext;
	wextend(sig_ext, sig, lf - 1, "sym");
	
	conv(result_a_ext, sig_ext, Lo_D);
	conv(result_d_ext, sig_ext, Hi_D);

	down_sample(result_a, result_a_ext);
	down_sample(result_d, result_d_ext);
}


/*���� approx��detail(a,d) ���� x_rec reconstruction
*	ԭʼ�źų��� lx
*	a, d���� int((lx+lf-1)/2)
*	�ع�x_rec���� 2*(int((lx+lf-1)/2)) - lf + 2
*/
void DWT::idwt(vector<float> &sig_rec, vector<float> const&in_a, vector<float> const&in_d){
	if (in_a.size() != in_d.size()){
		cout << "ERROR: length of approx signal and detail signal not equal when call DWT::idwt" << endl;
	}
	vector<float> a_conv;
	vector<float> d_conv;
	upsconv(a_conv, in_a, Lo_R);
	upsconv(d_conv, in_d, Hi_R);
	sig_rec.resize(2 * in_a.size() - lf + 2);
	//cout << a_conv.size() << endl;
	//cout << sig_rec.size() << endl;
	for (int i = 0; i < sig_rec.size(); i++){
		sig_rec[i] = a_conv[i] + d_conv[i];
	}
}

/*vectorƴ��	
	type = 0 �ı�a ��bƴ�ӵ�a����	a[1,2],b[3,4]->a[1,2,3,4],b[3,4]
	type = 1 �ı�a ��aƴ�ӵ�b����	a[1,2],b[3,4]->a[1,2],b[1,2,3,4]
*/
inline static
void vector_merge(vector<float> &a, vector<float> &b, int type){
	if (type == 0){
		int a_size0 = a.size();
		a.resize(a.size() + b.size());
		memcpy(&a[a_size0], &b[0], b.size()*sizeof(float));
		return;
	}
	if (type == 1){
		int a_size0 = a.size();
		a.resize(a.size() + b.size());
		//for (int i = 0; i < a.size(); i++){
		//	cout << a[i] << " ";
		//}cout << endl;
		for (int i = a.size() - 1; i >= b.size(); i--){
			a[i] = a[i - b.size()];
		}
		memcpy(&a[0], &b[0], b.size()*sizeof(float));
	}
}
/*WAVEDEC Multi-level 1-D wavelet decomposition.
*	The output vector, C, contains the wavelet decomposition. L contains the number of coefficients by level.
*	C and L are organized as:
*		C		= [app. coef.(N)|det. coef.(N)|... |det. coef.(1)]
*		L(1)	= length of app. coef.(N)	
*		L(i)   = length of det. coef.(N-i+2) for i = 2,...,N+1
*		L(N+2) = length(X)
*/
bool DWT::wavedec(vector<float> &result_c, vector<int> &result_l, vector<float> sig, int n){
	//cout << log2f(sig.size()) << endl;
	if (n > int(log2f(sig.size()) - 1)) {
		cout << "WARNNING: level of wavedec too large << endl" << endl;
		return false;
	}

	result_l = vector<int>(n + 2, 0);
	result_l[n + 1] = sig.size();
	result_c.clear();

	vector<float> sig_tmp = sig;
	vector<float> a_tmp;
	vector<float> d_tmp;
	for (int k = 1; k <= n; k++){
		dwt(a_tmp, d_tmp, sig_tmp);
		sig_tmp = a_tmp;
		vector_merge(result_c, d_tmp, 1);
		result_l[n + 1 - k] = d_tmp.size();
	}
	vector_merge(result_c, a_tmp, 1);
	result_l[0] = a_tmp.size();
	return true;
}

/*��ȡn-level detail coefficients
	����c(coefs), l(longs)������level-n ��� 
	��ʼλ��cusum(c,index)+1 ����Ϊ c[index]��Ƭ��
	��	c[149] l[27,27,37,58,100]
		n = 1	result =	c(92:149)(int matlab c:(91:148))
		n = 3	result =	c(28:54)
	index = nmax -  n + 1 (1=<n<=nmax)
*/
void DWT::detcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n){
	int nmax =in_l.size() - 2;
	int index = nmax - n + 1;
	int len = in_l[index];
	int start = 0;
	for (int i = 0; i < index; i++){
		start += in_l[i];
	}
	result.resize(len);
	memcpy(&result[0], &in_c[start], len*sizeof(float));
}

/*��ȡn-level approximation coefficients
	0=<n<=nmax	(0���Ǻ�ԭʼ�źų��Ȼ���һ���Ļ�ԭ�ź�)
*/
void DWT::appcoef(vector<float> &result, vector<float> &in_c, vector<int> &in_l, int n){
	int rmax = in_l.size();
	int nmax = rmax - 2;
	//a_tmp ��ʼ��Ϊ nmax level �� approx coef
	vector<float> a_tmp;
	a_tmp.resize(in_l[0]);
	memcpy(&a_tmp[0], &in_c[0], in_l[0] * sizeof(float));
	result = a_tmp;
	vector<float> d_tmp;
	for (int i = nmax; i > n; i--){
		detcoef(d_tmp, in_c, in_l, i);
		idwt(result, a_tmp, d_tmp);
		result.resize(in_l[nmax - i + 2]);
		a_tmp = result;
	}
}

/*reconstruction(wavedec����任)*/
void DWT::waverec(vector<float> &result, vector<float> &in_c, vector<int> &in_l){
	appcoef(result, in_c, in_l, 0);
}






