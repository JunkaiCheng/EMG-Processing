#include "test_fft.h"
#include "algo_ifft.h"
#include "algo_ft_filter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>

#include <vector>
using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

void read_fft_data_series(std::string filename, CDataSeries& data_series)
{
	std::ifstream infile(filename.c_str(), std::ios::in);

	while (!infile.eof())
	{
		std::string line_str;
		std::getline(infile, line_str);

		std::stringstream s_stream(line_str);
		float val;
		s_stream >> val;
		data_series.push_back(val);
	}

	infile.close();
}

void write_fft_data_series(std::string filename, CDataSeries& data_series)
{
	std::ofstream outfile(filename.c_str(), std::ios::out);

	for (size_t i = 0; i < data_series.size(); i++)
	{
		outfile << data_series[i] << '\n';
	}

	outfile.close();
}

void test_fft()
{
	CDataSeries dataseries;
	read_fft_data_series(std::string("test/fft/src_data.txt"), dataseries);

	std::shared_ptr<CData> indata = std::make_shared<CData>();
	indata->resizeOutputData(10);

	for (size_t i = 0; i < 10; i++)
	{
		indata->setDataSeries(i, dataseries);
	}

	std::shared_ptr<CAlgoFFT> algo = std::make_shared<CAlgoFFT>();

	algo->setInputData(indata);

	algo->execute();

	std::shared_ptr<CDataFFT> datafft = std::dynamic_pointer_cast<CDataFFT, CData>(algo->getOutputData());

	size_t sel_idx = 3;

	CDataSeries dst_dataseries;
	datafft->getDataSeries(sel_idx, dst_dataseries);

	write_fft_data_series(std::string("test/fft/dst_data.txt"), dst_dataseries);

}

void test_ifft()
{
	CDataSeries dataseries;
	read_fft_data_series(std::string("test/fft/src_data.txt"), dataseries);
	std::shared_ptr<CData> indata = std::make_shared<CData>();
	indata->resizeOutputData(10);
	for (size_t i = 0; i < 10; i++)
	{
		indata->setDataSeries(i, dataseries);
	}

	std::shared_ptr<CAlgoFFT> algo = std::make_shared<CAlgoFFT>();
	algo->setInputData(indata);
	algo->execute();

	std::shared_ptr<CAlgoIFFT> ifft_algo = std::make_shared<CAlgoIFFT>();
	ifft_algo->setInputData(algo->getOutputData());
	ifft_algo->execute();

	std::shared_ptr<CData> out_data = ifft_algo->getOutputData();

	CDataSeries out_data_series;
	out_data->getDataSeries(4, out_data_series);

}

// 2019 - 4 - 8 add by YuanJian

//#ifdef DEBUG
inline static
void print_vec(vector<float> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}
inline static
void print_vec(vector<complex<float>> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}
//读入文本至vector
inline static void read_in(vector<CDataSeries>&data, string filename, int channel, int length) {
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
//写出vector至文本
inline static void  write_out(vector<CDataSeries>&data, string filename, int channel, int length) {
	ofstream fout(filename);
	for (int i = 0; i < channel; i++) {
		for (int j = 0; j < length; j++) {
			fout << data[i][j] << " ";
		} fout << endl;
	}
	fout.close();
}
//#endif // DEBUG

void yj_test1() {
	//data
	vector<CDataSeries> data;	data.resize(2);
	CDataSeries v1(20, 1);
	CDataSeries v2(20, 1); for (int i = 1; i < 10; i++)v2[i] = i + 1;
	data[0] = v1; data[1] = v2;
	shared_ptr<CData> data_sp = shared_ptr<CData>(new CData);
	data_sp->setOutputData(data);
	//algo fft
	shared_ptr<CAlgo> algo_sp = shared_ptr<CAlgo>(new CAlgoFFT);
	algo_sp->setInputData(data_sp);
	algo_sp->execute();

	//algo filter
	shared_ptr<CParamFtFilter> param_sp = shared_ptr<CParamFtFilter>(new CParamFtFilter);
	param_sp->setValue("pass", 0.1f, 0.9f);
	shared_ptr<CAlgo> flt_sp = shared_ptr<CAlgo>(new CAlgoFtFilter);
	flt_sp->setInputData(algo_sp->getOutputData());
	flt_sp->setParam(param_sp);
	flt_sp->execute();

	//algo ifft
	shared_ptr<CAlgo> algo2_sp = shared_ptr<CAlgo>(new CAlgoIFFT);
	algo2_sp->setInputData(flt_sp->getOutputData());
	algo2_sp->execute();

#ifdef DEBUG
	print_vec((algo2_sp->getOutputData())->getOutputData()[1]);
#endif // DEBUG
}
void yj_test2(){
	// 读入数据
	vector<CDataSeries>		data;
	//read_in(data, "D:\\YJ\\EEG\\yj\\data\\ft_in2.txt", 1, 1500);
	read_in(data, "data\\ft_in2.txt", 1, 1500);
	shared_ptr<CData> data_sp = shared_ptr<CData>(new CData);
	data_sp->setOutputData(data);
	// filter
	shared_ptr<CParamFtFilter> param_sp = shared_ptr<CParamFtFilter>(new CParamFtFilter);
	param_sp->setValue("pass", (100.0f) / 500, (300.0f) / 500);
	shared_ptr<CAlgo> flt_sp = shared_ptr<CAlgo>(new CAlgoFtFilter);
	flt_sp->setInputData(data_sp);
	flt_sp->setParam(param_sp);
	flt_sp->execute();

	vector<CDataSeries>		data_out = flt_sp->getOutputData()->getOutputData();
	write_out(data_out, "data\\ft_out2.txt", 1, 1500);
}

//void yj_test3(){
//	// 读入数据
//	vector<CDataSeries>		data;
//	read_in(data, "D:/YJ/EEG/yj/matlab/Jin/1_butterworth_matlab/wave_stack.txt", 5, 629);
//	shared_ptr<CData> data_sp = shared_ptr<CData>(new CData);
//	data_sp->setOutputData(data);
//	// fft
//	shared_ptr<CAlgo> fft_sp = shared_ptr<CAlgo>(new CAlgoFFT);
//	fft_sp->setInputData(data_sp);
//	fft_sp->execute();
//	// filter
//	shared_ptr<CParamFtFilter> param_sp = shared_ptr<CParamFtFilter>(new CParamFtFilter);
//	param_sp->setValue("pass", (1.0f) / 500, (50.0f) / 500);
//	shared_ptr<CAlgo> flt_sp = shared_ptr<CAlgo>(new CAlgoFtFilter);
//	flt_sp->setInputData(fft_sp->getOutputData());
//	flt_sp->setParam(param_sp);
//	flt_sp->execute();
//	// ifft
//	shared_ptr<CAlgo> ifft_sp = shared_ptr<CAlgo>(new CAlgoIFFT);
//	ifft_sp->setInputData(flt_sp->getOutputData());
//	ifft_sp->execute();
//
//	vector<CDataSeries>		data_out = ifft_sp->getOutputData()->getOutputData();
//	write_out(data_out, "D:/YJ/EEG/yj/matlab/Jin/1_butterworth_matlab/wave_stack_out.txt",5, 629);
//}

END_MAVER_EMG_NAMESPACE