#include "AlgoMVC.h"
#include <iostream>
#include<sstream>
#include<stdafx.h>
#include"Algo_TS.h"
#include"Algo_Average.h"
#include"Algo_AEMG.h"
#include"Algo_IEMG.h"
#include<stdlib.h>
#include<time.h>
#include <iomanip>
#include"Algo_SamEn.h"
#include"Algo_RenyiEn.h"
#include <fstream>
#include "Estimate_TimeInterval.h"
#include"Algo_FractalDim.h"
#include"Algo_ApEn.h"
#include"Algo_FuzzyEn.h"
//#include"INTERPOLATION.h"
using namespace MaverEMG;
using namespace std;

std::shared_ptr<CData> CreateInputData(int size, int length);

void PrintRawData(const std::shared_ptr<CData>&C);


void TestMVC(const std::shared_ptr<CData>&C);

void TestTS(const std::shared_ptr<CData>&C, int dst_length);


void TestAverage(const std::shared_ptr<CData>&C, int dst_length);


void TestIENG(const std::shared_ptr<CData> &C, std::string method, float val);

void TestRenyiEn(const std::shared_ptr<CData>&C, int N, float r);



void TestAEMG(const std::shared_ptr<CData>&C);

bool Read_Data(string filepath, CDataSeries& dst, int start, int end);

void Print_list(CDataSeries& temp);

void Print_set(vector<CDataSeries>& temp);

void test_FractalDim();

void test_Entropy();
