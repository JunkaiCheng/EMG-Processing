#ifndef _MAVER_TEST_FFT_H_
#define _MAVER_TEST_FFT_H_

#include "data_fft.h"
#include "algo_fft.h"

BEGIN_MAVER_EMG_NAMESPACE

void read_fft_data_series(std::string filename, CDataSeries& data_series);

void write_fft_data_series(std::string filename, CDataSeries& data_series);

void test_fft();

void test_ifft();

// 2019 - 4 - 8 add by YuanJian

void yj_test1();
void yj_test2();
//void yj_test3();

END_MAVER_EMG_NAMESPACE

#endif // !_MAVER_TEST_FFT_H_
