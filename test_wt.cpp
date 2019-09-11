#include "test_wt.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace MaverEMG;

//���vector
void print_vec(vector<float> &v) {
	int n = v.size();
	int row = 10;
	//cout << "size: " << v.size() << endl;
	for (int i = 0; i < n; i++) {
		cout << v[i] << " ";
		if ((i + 1) % row == 0 || i == n - 1) cout << endl;
	}
}
inline static void read_in(vector<vector<float>>&data, string filename, int channel, int length) {
	data.resize(channel);
	for (int i = 0; i < channel; i++) data[i].resize(length);
	ifstream fin(filename);
	for (int i = 0; i < channel; i++) {
		for (int j = 0; j < length; j++) {
			fin >> data[i][j];
		}
	}
	fin.close();
}
inline static void read_in(vector<float>&data, string filename, int length) {
	data.resize(length);
	ifstream fin(filename);
	for (int i = 0; i < length; i++) {
		fin >> data[i];
	}
	fin.close();
}
//д��vector���ı�
inline static void  write_out(vector<vector<float>>&data, string filename, int channel, int length) {
	ofstream fout(filename);
	for (int i = 0; i < channel; i++) {
		for (int j = 0; j < length; j++) {
			fout << data[i][j] << " ";
		} fout << endl;
	}
	fout.close();
}
inline static void  write_out(vector<vector<int>>&data, string filename, int channel, int length) {
	ofstream fout(filename);
	for (int i = 0; i < channel; i++) {
		for (int j = 0; j < length; j++) {
			fout << data[i][j] << " ";
		} fout << endl;
	}
	fout.close();
}
inline static void write_out(vector<float>&data, string filename, int length) {
	ofstream fout(filename);
	for (int i = 0; i < length; i++) {
		fout << data[i] << " ";
	}
	fout.close();
}
inline static void write_out(vector<int>&data, string filename, int length) {
	ofstream fout(filename);
	for (int i = 0; i < length; i++) {
		fout << data[i] << " ";
	}
	fout.close();
}

// ---------- dwt.h ----------
void yj_wt_test1() {
	DWT obj;
	obj.set_filters("sym10");
	obj.print_filters();
}

//	���� dwt idwt
void yj_wt_test2() {
	DWT obj;
	obj.set_filters("sym10");
	vector<float> v_in, a, d, v_out;		
	read_in(v_in, "D:\\Project\\Code_matlab\\leleccum.txt",4320);
	obj.dwt(a, d, v_in);
	write_out(a, "D:\\Project\\Code_matlab\\a.txt", a.size());
	write_out(d, "D:\\Project\\Code_matlab\\d.txt", a.size());
	obj.idwt(v_out, a, d);
	write_out(v_out, "D:\\Project\\Code_matlab\\out.txt", v_out.size());

}

//	���� wavedec appcoef waverec
void yj_wt_test3() {
	DWT obj;
	obj.set_filters("sym10");
	vector<float> v_in, c, v_out, v_app_3;
	vector<int> l;
	read_in(v_in, "D:\\Project\\Code_matlab\\leleccum.txt", 4320);
	obj.wavedec(c, l, v_in, 5);
	//write_out(c, "D:\\Project\\Code_matlab\\c.txt", c.size());
	//write_out(l, "D:\\Project\\Code_matlab\\l.txt", l.size());
	obj.waverec(v_out, c,l);
	obj.appcoef(v_app_3, c, l, 5);
	//write_out(v_out, "D:\\Project\\Code_matlab\\out.txt", v_out.size());
	write_out(v_app_3, "D:\\Project\\Code_matlab\\app.txt", v_app_3.size());
}

// ---------- algo_wt.h ----------
void yj_wt_test4() {
	// ��������
	vector<CDataSeries>		data;
	read_in(data, "data\\leleccum.txt", 1, 4320);

	shared_ptr<CData>			data_sp = shared_ptr<CData>(new CData);
	data_sp->setOutputData(data);
	//wt
	shared_ptr<CParamWT> param_sp = shared_ptr<CParamWT>(new CParamWT);
	param_sp->setValue("sym10",  5); //level>0
	shared_ptr<CAlgo> wt_sp = shared_ptr<CAlgo>(new CAlgoWT);
	wt_sp->setParam(param_sp);
	wt_sp->setInputData(data_sp);
	wt_sp->execute();
	//iwt
	shared_ptr<CParamWT> param2_sp = shared_ptr<CParamWT>(new CParamWT);
	/*��任ʱ�ڶ����������������任��ͬ
		-	���(������5)ʱΪ���Ƶϵ�� �������
		-	��С(0)ʱΪ���Ⱥ�ԭ��һ���Ļ�ԭ�ź�
	*/
	param2_sp->setValue("sym10", 3);
	shared_ptr<CAlgo> iwt_sp = shared_ptr<CAlgo>(new CAlgoIWT);
	iwt_sp->setParam(param2_sp);
	iwt_sp->setInputData(wt_sp->getOutputData());
	iwt_sp->execute();

	vector<CDataSeries> data_out = iwt_sp->getOutputData()->getOutputData();
	//vector<vector<int>> data_out = dynamic_pointer_cast<CDataWT>( wt_sp->getOutputData())->getLongs();
	write_out(data_out, "data\\leleccum_out.txt", data_out.size(), data_out[0].size());
}

// ---------- algo_wt_filter.h ----
void yj_wt_test5() {
	// ��������
	vector<CDataSeries>		data;
	read_in(data, "data\\ft_in1.txt", 1, 1500);
	//read_in(data, "data\\emg1.txt", 1, 61531);
	shared_ptr<CData> data_sp = shared_ptr<CData>(new CData);
	data_sp->setOutputData(data);

	//filter
	shared_ptr<CParamWtFilter> param_sp = make_shared<CParamWtFilter>("CParamWtFilter");
	param_sp->setValue("sqtwolog", "s", "mln" , 6, "sym9");
	shared_ptr<CAlgoWtFilter> filt_sp = make_shared<CAlgoWtFilter>();
	filt_sp->setInputData(data_sp);
	filt_sp->setParam(param_sp);
	filt_sp->execute();

	vector<CDataSeries> data_out = filt_sp->getOutputData()->getOutputData();
	write_out(data_out, "D:\\Project\\Code_matlab\\emg1_out.txt", data_out.size(), data_out[0].size());
}

void yj_wt_test6() {
	shared_ptr<CAlgoWtFilter> filt_sp = make_shared<CAlgoWtFilter>();

	//float v[] = { 1.2,2.3,3.4,4.5 };
	//vector<float> data(v, v+4);
	//float thr = filt_sp->thselect(data, "heursure");
	//cout << "thr = " << thr << endl;

	float v[] = { 5,1,6,3,7,8 };
	vector<float> data(v, v + 6);
	float thr = filt_sp->median_abs(data);
	cout << "thr = " << thr << endl;
}