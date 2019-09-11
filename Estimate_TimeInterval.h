//用于估测序列的延时时间 by hebaoxiang 2019-04017
#ifndef _MAVER_EMG_ESTIMATE_TIMEINTERVAL_H
#define _MAVER_EMG_ESTIMATE_TIMEINTERVAL_H
#include"data.h"
#include <algorithm>
BEGIN_MAVER_EMG_NAMESPACE
//例如 src=[[3,12,24,15,5,74,23,54,31,23,64,75]; interval_num=5;可将src分为[0,10,25,50,75],bincounts=[2 5 1 3 1] ind=[1 2 2 2..]
void Histc(const CDataSeries& src, const CDataSeries& comp, int interval_num, std::vector<int> &bincounts,std::vector<int>&ind);

//计算相关信息熵

float MutualInformation(std::vector<int>&bincounts_x, std::vector<int>&ind_x, std::vector<int>&bincounts_y, std::vector<int>&ind_y);

int Get_TimeInterval(CDataSeries& src,int length);

float euclideanDist(int tau, CDataSeries& data_series, int m, int k, int l);

float shortestDistance(int tau, CDataSeries& data_series, int i, int d);

int nearestNeighbor(int tau, CDataSeries& data_series, int i, int d);

int  detE(int tau, CDataSeries& data_series);

int ranE(int tau, CDataSeries& data_series);
END_MAVER_EMG_NAMESPACE
#endif // !_MAVER_EMG_ESTIMATE_TIMEINTERVAL_H

