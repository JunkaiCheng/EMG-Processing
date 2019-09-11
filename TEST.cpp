#include"TEST.h"
using namespace MaverEMG;
using namespace std;

std::shared_ptr<CData> CreateInputData(int size, int length)
{
	srand(time(NULL));
	std::shared_ptr<CData> C = std::make_shared<CData>();
	C->setClassName("my_name");
	C->resizeOutputData(size);
	CDataSeries data_1;
	for (auto j = 0; j < size; j++)
	{
		for (auto i = 0; i < length; i++)
			data_1.push_back(float(rand() % 5)*0.1 + rand() % 4);
		C->setDataSeries(j, data_1);
		data_1.clear();
	}
	return C;
}

void PrintRawData(const std::shared_ptr<CData>&C)
{
	std::vector<CDataSeries> cc = C->getOutputData();
	std::cout << "raw data（原始数据）:" << std::endl;
	for (size_t i = 0; i < cc.size(); i++)
	{
		for (size_t j = 0; j < cc[i].size(); j++)
		{
			std::cout << std::setw(3) << cc[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void TestMVC(const std::shared_ptr<CData>&C)
{
	std::shared_ptr<CParam_MVC> param = std::make_shared<CParam_MVC>();
	CAlgoMVC mvc;
	mvc.setParam(param);
	mvc.setInputData(C);
	mvc.execute();
	std::shared_ptr<CData> output = mvc.getOutputData();
	std::vector<CDataSeries> result = output->getOutputData();
	std::cout << "MVC（幅度/最大幅度）:" << std::endl;
	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void TestTS(const std::shared_ptr<CData>&C, int dst_length)
{
	std::shared_ptr<CParam_TS> param = std::make_shared<CParam_TS>();
	param->Set_dstLength(dst_length);
	CAlgo_TS ts;
	ts.setParam(param);
	ts.setInputData(C);
	ts.execute();
	std::shared_ptr<CData> output = ts.getOutputData();
	std::vector<CDataSeries> result = output->getOutputData();
	std::cout << "TS（时间标准化）:" << std::endl;
	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void TestAverage(const std::shared_ptr<CData>&C, int dst_length)
{
	std::shared_ptr<CParam_Average> param = std::make_shared<CParam_Average>();
	param->Set_dstLength(dst_length);
	CAlgo_Average ave;
	ave.setParam(param);
	ave.setInputData(C);
	ave.execute();
	std::shared_ptr<CData> output = ave.getOutputData();
	std::vector<CDataSeries> result = output->getOutputData();
	std::cout << "TS averaged list（幅度、时间标准化）:" << std::endl;
	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::shared_ptr<CData_Average> m_output = std::make_shared<CData_Average>(*dynamic_cast<CData_Average*>(output.get()));
	CDataSeries ave_list = m_output->GetMeanList();
	std::cout << "TS mean list(平均值):" << std::endl;
	for (size_t i = 0; i < ave_list.size(); i++)
	{

		std::cout << ave_list[i] << " ";
	}
	std::cout << std::endl;
}

void TestIENG(const std::shared_ptr<CData> &C, std::string method, float val)
{
	std::shared_ptr<CParam_IEMG> param = std::make_shared<CParam_IEMG>();
	param->SetIntMethod(method);
	param->SetIntValue(val);
	CAlgo_IEMG iemg;
	iemg.setParam(param);
	iemg.setInputData(C);
	iemg.execute();
	std::shared_ptr<CData> output = iemg.getOutputData();
	std::vector<CDataSeries> result = output->getOutputData();
	std::cout << "IEMG（肌电积分值）:" << std::endl;
	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void TestRenyiEn(const std::shared_ptr<CData>&C, int N, float r)
{
	std::shared_ptr<CParam_RenyiEn> param = make_shared<CParam_RenyiEn>();
	param->SetOrder(r);
	param->SetSubSectionNum(N);
	CAlgo_RenyiEn re;
	re.setParam(param);
	re.setInputData(C);
	re.execute();
	std::shared_ptr<CData> output = re.getOutputData();
	std::shared_ptr<CData_SamEn> out = std::make_shared<CData_SamEn>(*dynamic_cast<CData_SamEn*>(output.get()));
	cout << "renyi entropy:" << endl;
	CDataSeries entropy = out->GetEnValue();
	for (size_t i = 0; i < entropy.size(); i++)
	{
		cout << entropy[i] << " ";
	}
	cout << endl;

}


void TestAEMG(const std::shared_ptr<CData>&C)
{
	CAlgo_AEMG aemg;
	aemg.setInputData(C);
	aemg.setParam(std::make_shared<CParam_AEMG>());
	aemg.execute();
	aemg.execute_RMS();
	aemg.execute_MSD();
	aemg.execute_CrossZeroRate();
	aemg.execute_MaxVal();
	std::shared_ptr<CData_AEMG> out = std::make_shared<CData_AEMG>(*dynamic_cast<CData_AEMG*>(aemg.getOutputData().get()));
	CDataSeries result = out->GetAEMG();
	std::cout << "AEMG（平均整流肌电值）:" << std::endl;

	for (size_t i = 0; i < result.size(); i++)
	{
		std::cout << std::setw(3) << result[i] << " ";


	}
	std::cout << std::endl;
	std::cout << "RMS（均方根值）:" << std::endl;
	result = out->GetRMS();
	for (size_t i = 0; i < result.size(); i++)
	{
		std::cout << std::setw(3) << result[i] << " ";


	}
	std::cout << std::endl;
	std::cout << "MSD（均方差）:" << std::endl;
	result = out->GetMSD();
	for (size_t i = 0; i < result.size(); i++)
	{
		std::cout << std::setw(3) << result[i] << " ";


	}
	std::cout << std::endl;
	std::cout << "CrossZeroRate（过零率）:" << std::endl;
	result = out->GetCrossZeroRate();
	for (size_t i = 0; i < result.size(); i++)
	{
		std::cout << std::setw(3) << result[i] << " ";


	}
	std::cout << std::endl;
	std::cout << "MaxVal（最大值）:" << std::endl;
	result = out->GetMaxVal();
	for (size_t i = 0; i < result.size(); i++)
	{
		std::cout << std::setw(3) << result[i] << " ";


	}
	std::cout << std::endl;
}

bool Read_Data(string filepath, CDataSeries& dst, int start, int end)//读取文件中start行到end行的数据；保存在dst数组中
{
	ifstream infile;
	infile.open(filepath);
	if (!infile.is_open())
		return false;
	else
	{
		dst.clear();
		string s;
		for (size_t i = 0; i < start; i++)
			getline(infile, s);
		for (size_t i = 0; i <= end - start; i++)
		{
			getline(infile, s);
			dst.push_back(atof(s.c_str()));
		}
	}
}

void Print_list(CDataSeries& temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		cout << temp[i] << " ";
	}
	cout << endl;
}

void Print_set(vector<CDataSeries>& temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		for (size_t j = 0; j < temp[i].size(); j++)
		{
			cout << temp[i][j] << " ";
		}
		cout << endl;

	}
}

void test_FractalDim()
{
	std::shared_ptr<CData> C = std::make_shared<CData>();
	C->setClassName("my_name");
	C->resizeOutputData(1);
	CDataSeries data_1;
	for (auto j = 0; j < 1; j++)
	{
		Read_Data(string("D:\\emg\\Maver_EMG_Algo\\Maver_EMG_Algo\\sample.txt"), data_1, 2500, 3200);
		C->setDataSeries(j, data_1);
		data_1.clear();
	}
	CAlgo_FractalDim fd;
	fd.setInputData(C);
	std::shared_ptr<CParam_FractalDim> param = make_shared<CParam_FractalDim>();
	param->SetParam(0.8, 10);
	fd.setParam(param);
	fd.execute();
	std::shared_ptr<CData_FractalDim> myout = std::dynamic_pointer_cast<CData_FractalDim>(fd.getOutputData());
	CDataSeries coe = myout->GetDimList();
	cout << "dim is :" << endl;
	Print_list(coe);
}

void test_Entropy()
{
	std::shared_ptr<CData> C = std::make_shared<CData>();
	C->setClassName("my_name");
	C->resizeOutputData(1);
	CDataSeries data_1;
	for (auto j = 0; j < 1; j++)
	{
		Read_Data(string("D:\\emg\\Maver_EMG_Algo\\Maver_EMG_Algo\\sample.txt"), data_1, 2500, 3200);
		C->setDataSeries(j, data_1);
		data_1.clear();
	}
	//样本熵
	CAlgo_SamEn samen;
	std::shared_ptr<CParam_SamEn> param = std::make_shared<CParam_SamEn>();
	param->SetEnDim(2);
	param->SetTolerance(0.08);//data的std*0.1-0.25
	samen.setInputData(C);
	samen.setParam(param);
	samen.execute();
	std::shared_ptr<CData_SamEn> myout = std::dynamic_pointer_cast<CData_SamEn>(samen.getOutputData());
	CDataSeries coe = myout->GetEnValue();
	cout << "Sample Entropy is :" << endl;
	Print_list(coe);
	cout << "Approximate Entropy is: " << endl;
	//近似熵
	CAlgo_ApEn apmen;
	apmen.setInputData(C);
	apmen.setParam(param);
	apmen.execute();
	myout = std::dynamic_pointer_cast<CData_SamEn>(apmen.getOutputData());
	coe = myout->GetEnValue();
	Print_list(coe);
	//fuzzy 熵
	cout << "Fuzzy Entropy is: " << endl;
	CAlgo_FuzzyEn fuzzy;
	fuzzy.setInputData(C);
	fuzzy.setParam(param);
	fuzzy.execute();
	std::shared_ptr<CData_SamEn> myout_fuzzy = std::dynamic_pointer_cast<CData_SamEn>(fuzzy.getOutputData());
	coe = myout_fuzzy->GetEnValue();
	Print_list(coe);
	//Renyi 熵
	cout << "Renyi Entropy is:" << endl;
	std::shared_ptr<CParam_RenyiEn> param_renyi = make_shared<CParam_RenyiEn>();
	param_renyi->SetOrder(0.4);
	param_renyi->SetSubSectionNum(10);
	CAlgo_RenyiEn re;
	re.setParam(param_renyi);
	re.setInputData(C);
	re.execute();
	std::shared_ptr<CData> output = re.getOutputData();
	std::shared_ptr<CData_SamEn> out_renyi = std::make_shared<CData_SamEn>(*dynamic_cast<CData_SamEn*>(output.get()));
	CDataSeries entropy = out_renyi->GetEnValue();
	for (size_t i = 0; i < entropy.size(); i++)
	{
		cout << entropy[i] << " ";
	}
	cout << endl;

}
