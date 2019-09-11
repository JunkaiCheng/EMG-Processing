#include "test_fda.h"

#include <fstream>
#include <iostream>
using namespace std;
using namespace MaverEMG;

//输出vector
inline static void print_vec(vector<float> &v) {
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
//写出vector至文本
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

void yj_fda_test1() {
	// 读入数据
	vector<CDataSeries>		data;
	read_in(data, "D:\\Project\\Code_matlab\\mf_in1.txt", 1, 1500);
	shared_ptr<CData> data_sp = shared_ptr<CData>(new CData);
	data_sp->setOutputData(data);

	//fda
	shared_ptr<CParamFDA> param_sp = make_shared<CParamFDA>();
	param_sp->setParams("MF", 1000);
	shared_ptr<CAlgoFDA> fda_sp = make_shared<CAlgoFDA>();
	fda_sp->setInputData(data_sp);
	fda_sp->setParam(param_sp);
	fda_sp->execute();

	vector<CDataSeries> data_out = fda_sp->getOutputData()->getOutputData();
	
	write_out(data_out, "D:\\Project\\Code_matlab\\mf_out.txt", data_out.size(), data_out[0].size());
}