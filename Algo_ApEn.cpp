#include "Algo_ApEn.h"

BEGIN_MAVER_EMG_NAMESPACE
static std::vector<CDataSeries> CreateSequence(CDataSeries& data, int m)
{
	std::vector<CDataSeries> result;
	CDataSeries v;
	for (size_t i = 0; i < data.size() - m + 1; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			v.push_back(data[i + j]);
		}
		result.push_back(v);
		v.clear();
	}
	return result;
}
static std::vector<CDataSeries> GetDistance(std::vector<CDataSeries>&data, int dim)
{
	std::vector<CDataSeries> result;
	CDataSeries temp1;
	CDataSeries temp2;
	int size = data.size();
	float max = 0;
	result.resize(size);
	for (size_t i = 0; i < size; i++)
		result[i].resize(size);
	for (size_t i = 0; i < size; i++)
	{
		temp1 = data[i];
		for (size_t j = i + 1; j < size; j++)
		{
			max = 0;
			temp2 = data[j];
			for (int k = 0; k < dim; k++)
			{
				if (abs(temp1[k] - temp2[k]) >= max)
					max = abs(temp1[k] - temp2[k]);
			}
			result[i][j] = max;
			result[j][i] = max;
		}
	}
	return result;
}
static float SumDistLessThanTolerance1(std::vector<CDataSeries>&input, float r)
{
	float output = 0;
	int sum = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		sum = 0;
		for (size_t j = 0; j < input[i].size(); j++)
		{
			
				if (input[i][j] <= r)
					sum += 1;
		
		}
		output += log(float(sum)/input[i].size());
	}
	return output;
}
CAlgo_ApEn::CAlgo_ApEn() : CAlgo("CAlgo_ApEn")
{
	m_param = std::make_shared<CParam_SamEn>("Param SamEn");
	m_output = std::make_shared<CData_SamEn>("Data SamEn");
}


CAlgo_ApEn::~CAlgo_ApEn()
{
}

CAlgo_ApEn::CAlgo_ApEn(const CAlgo_ApEn& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_ApEn::CAlgo_ApEn(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_SamEn>("Param SamEn");
	m_output = std::make_shared<CData_SamEn>("Data SamEn");
}

CAlgo_ApEn& CAlgo_ApEn::operator = (const CAlgo_ApEn& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_ApEn::clone() const
{
	return new CAlgo_ApEn(*this);
}

std::shared_ptr<CObject> CAlgo_ApEn::clone_shared() const
{
	return std::make_shared<CAlgo_ApEn>(*this);
}

bool CAlgo_ApEn::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_ApEn*>(ptr) != nullptr;
}

bool CAlgo_ApEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_ApEn::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_ApEn::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_SamEn>(*dynamic_cast<CParam_SamEn*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_ApEn::execute()
{
	std::vector<CDataSeries> input = m_input->getOutputData();
	CDataSeries temp_sam;
	int dim = m_param->GetEnDim();// embedding dimension
	float r = m_param->GetTolerance();//tolerance
	float sum_m;
	float sum_m1;//dim 为m和dim为m1的计数次数
	int N;
	for (size_t i = 0; i < input.size(); i++)
	{
		sum_m = 0;
		sum_m1 = 0;
		N = input[i].size();
		std::vector<CDataSeries> sequence = CreateSequence(input[i], dim);//得到若干个长度为dim的序列
		std::vector<CDataSeries> dist_m = GetDistance(sequence, dim);//得到序列间的距离
		sum_m = SumDistLessThanTolerance1(dist_m, r);
		sequence.clear();
		dist_m.clear();
		sequence = CreateSequence(input[i], dim + 1);
		dist_m = GetDistance(sequence, dim + 1);
		sum_m1 = SumDistLessThanTolerance1(dist_m, r);
		temp_sam.push_back(sum_m/(N-dim+1)-sum_m1/(N-dim));
	}
	m_output->SetEnValue(temp_sam);

	return true;
}

std::shared_ptr<CData> CAlgo_ApEn::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE

