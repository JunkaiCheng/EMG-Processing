#include "Algo_FractalDim.h"
#include<fstream>
using namespace std;
BEGIN_MAVER_EMG_NAMESPACE

static std::vector<CDataSeries> GetPointSet(CDataSeries& series, int dim, int interval)
{
	int length = series.size();
	std::vector<CDataSeries> out;
	CDataSeries temp;
	for (int j = 0; j < length - (dim - 1)*interval; j++)
	{
		temp.clear();
		for (int i = 0; i < dim; i++)
		{
			temp.push_back(series[j + i*interval]);
		}
		out.push_back(temp);
	}
	return out;
}

static bool Dist_of_two_list(CDataSeries& A, CDataSeries& B, float& sum)
{
	if (A.size() != B.size())
	{
		return false;
	}
	else
	{
		sum = 0;
		for (size_t i = 0; i < A.size(); i++)
		{
			sum += pow(A[i] - B[i], 2);
		}
		sum = pow(sum, 0.5);
		return true;
	}
}

static std::vector<CDataSeries> GetDistance(std::vector<CDataSeries>&input)
{
	std::vector<CDataSeries> output;
	int size = input.size();
	output.resize(size);
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		output[i].resize(size, 0);
	}
	for (size_t i = 0; i < size; i++)
	{
		output[i][i] = 0;
		for (size_t j = i + 1; j < size; j++)
		{
			if (Dist_of_two_list(input[i], input[j], sum))
			{
				output[i][j] = sum;
				output[j][i] = sum;
			}
			else continue;
		}
	}
	return output;
}
//
static void GetCorrInt(const CDataSeries& r, CDataSeries& C, const std::vector<CDataSeries>& dist)
{
	C.resize(r.size());
	float sum = 0;
	for (size_t i = 0; i < r.size(); i++)
	{
		for (int j = 0; j < dist.size(); j++)
		{
			for (int k = 0; k < dist.size(); k++)
			{
				if (dist[j][k] < r[i])
					sum += 1;

			}

		}
		C[i] = sum * 2 / dist.size() / (dist.size() - 1);
		sum = 0;
	}
	//ofstream outfile("data.txt", ios::trunc);
	//for (int i = 0; i < r.size(); i++)
	//{
	//	outfile << r[i] << " " << C[i] << "\n";
	//}
	//outfile.close();
}


CAlgo_FractalDim::CAlgo_FractalDim() : CAlgo("CAlgo_FractalDim")
{
	m_output = std::make_shared<CData_FractalDim>("Data_FractalDim");
	m_param = std::make_shared<CParam_FractalDim>("Param_FractalDim");
}


CAlgo_FractalDim::~CAlgo_FractalDim()
{
}

CAlgo_FractalDim::CAlgo_FractalDim(const CAlgo_FractalDim& rhs) : CAlgo(rhs)
{
	CAlgo_FractalDim::operator=(rhs);
}

CAlgo_FractalDim::CAlgo_FractalDim(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CData_FractalDim>("Data_FractalDim");
}


CAlgo_FractalDim& CAlgo_FractalDim::operator = (const CAlgo_FractalDim& rhs)
{
	CAlgo::operator=(rhs);
	m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	m_output = std::dynamic_pointer_cast<CData_FractalDim>(rhs.m_output->clone_shared());
	m_param = std::dynamic_pointer_cast<CParam_FractalDim>(rhs.m_param->clone_shared());
	return *this;
}

CObject* CAlgo_FractalDim::clone() const
{
	return new CAlgo_FractalDim(*this);
}

std::shared_ptr<CObject> CAlgo_FractalDim::clone_shared() const
{
	return std::make_shared<CAlgo_FractalDim>(*this);
}

bool CAlgo_FractalDim::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgo_FractalDim*>(ptr) != nullptr;
}

bool CAlgo_FractalDim::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgo_FractalDim::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgo_FractalDim::setParam(std::shared_ptr<CParam> input_param)
{
	if (m_param->isSameKindAs(input_param))
	{
		m_param = std::make_shared<CParam_FractalDim>(*dynamic_cast<CParam_FractalDim*>(input_param.get()));
		return true;
	}
	else
		return false;
}

bool CAlgo_FractalDim::execute()
{
	std::vector<CDataSeries> input = m_input->getOutputData();
	CDataSeries dim_list;
	CDataSeries r;//it should be from m_param
	float ratio = m_param->GetRatio();
	int dst_length = 15;//插值过程中dst_size
	float k;
	for (int i = 0; i < m_param->Get_log_size(); i++)//r的选区一般较小即可，目前还没确定最优方案
	{
		r.push_back(0.04 + 0.001*i);
	}
	CDataSeries temp_r = r;
	CDataSeries c;
	std::vector<CDataSeries> point_set;
	for (size_t i = 0; i < input.size(); i++)
	{
		r = temp_r;
		int interval = Get_TimeInterval(input[i], input[i].size()*ratio);
		int dim = detE(interval, input[i]);
		if (dim == 9)
			dim = ranE(interval, input[i]);
		//std::cout << "tau is: " << interval << " m is: " << dim << std::endl;
		point_set = GetPointSet(input[i], dim, interval);
		GetCorrInt(r, c, GetDistance(point_set));
		int src_length = r.size();
		CDataSeries dst_x;
		CDataSeries dst_y;
		for (int i = 0; i < src_length; i++)
		{
			r[i] = log(r[i]);
			c[i] = log(c[i]);
		}
		for (int z = 0; z < dst_length; z++)
		{
			dst_x.push_back((r[src_length - 1] - r[0]) / dst_length*float(z) + r[0]);
		}
		interpolate(r, c, dst_x, dst_y);
		k = (dst_y[dst_length - 1] - dst_y[0]) / (dst_x[dst_length - 1] - dst_x[0]);
		dim_list.push_back(k);

	}
	m_output->SetDimList(dim_list);

	return true;
}

std::shared_ptr<CData> CAlgo_FractalDim::getOutputData()
{
	return m_output;
}



END_MAVER_EMG_NAMESPACE