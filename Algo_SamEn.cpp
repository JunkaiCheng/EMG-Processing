#include "Algo_SamEn.h"

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
static int SumDistLessThanTolerance(std::vector<CDataSeries>&input, float r)
{
	int output = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = i+1; j < input[i].size(); j++)
		{
			
				if (input[i][j] <= r)
					output += 1;
			
		}
	}
	return output;
}
CAlgo_SamEn::CAlgo_SamEn() : CAlgo("CAlgo_SamEn")
{
	m_param = std::make_shared<CParam_SamEn>("Param SamEn");
	m_output = std::make_shared<CData_SamEn>("Data SamEn");
}


CAlgo_SamEn::~CAlgo_SamEn()
{
}

CAlgo_SamEn::CAlgo_SamEn(const CAlgo_SamEn& rhs) : CAlgo(rhs)
{
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
}

CAlgo_SamEn::CAlgo_SamEn(const std::string& class_name) : CAlgo(class_name)
{
	m_param = std::make_shared<CParam_SamEn>("Param SamEn");
	m_output = std::make_shared<CData_SamEn>("Data SamEn");
}

CAlgo_SamEn& CAlgo_SamEn::operator = (const CAlgo_SamEn& rhs)
{
	setClassName(rhs.getClassName());
	m_input = rhs.m_input;
	m_output = rhs.m_output;
	m_param = rhs.m_param;
	return *this;
}

CObject* CAlgo_SamEn::clone() const
{
	return new CAlgo_SamEn(*this);
}

std::shared_ptr<CObject> CAlgo_SamEn::clone_shared() const
{
	return std::make_shared<CAlgo_SamEn>(*this);
}

bool CAlgo_SamEn::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_SamEn*>(ptr) != nullptr;
}

bool CAlgo_SamEn::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_SamEn::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_SamEn::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_SamEn>(*dynamic_cast<CParam_SamEn*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_SamEn::execute()
{
	std::vector<CDataSeries> input = m_input->getOutputData();
	CDataSeries temp_sam;
	int dim = m_param->GetEnDim();// embedding dimension
	float r = m_param->GetTolerance();//tolerance
	int sum_m, sum_m1;//dim 为m和dim为m1的计数次数
	int N;
	for (size_t i = 0; i < input.size(); i++)
	{
		sum_m = 0;
		sum_m1 = 0;
		N = input[i].size();
		std::vector<CDataSeries> sequence = CreateSequence(input[i], dim);//得到若干个长度为dim的序列
		std::vector<CDataSeries> dist_m = GetDistance(sequence, dim);//得到序列间的距离
		sum_m = SumDistLessThanTolerance(dist_m, r);
		sequence.clear();
		dist_m.clear();
		sequence = CreateSequence(input[i], dim+1);
		dist_m = GetDistance(sequence, dim+1);
		sum_m1 = SumDistLessThanTolerance(dist_m, r);
		temp_sam.push_back(-log(float(sum_m1)/sum_m));
	}
	m_output->SetEnValue(temp_sam);

	return true;
}

std::shared_ptr<CData> CAlgo_SamEn::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE

