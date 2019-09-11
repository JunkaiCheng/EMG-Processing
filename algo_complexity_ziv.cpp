/* algorithm of Lempel-ziv complexity by Junwei Deng*/

#include "algo_complexity_ziv.h"
#include <iostream>
#include<numeric>
#include<time.h>
#include<cmath>
BEGIN_MAVER_EMG_NAMESPACE

CAlgoComplexityZiv::CAlgoComplexityZiv() : CAlgo("CAlgoComplexityZiv")
{
	this->m_input = std::make_shared<CData>("Complexity_Ziv_input");
	this->m_output = std::make_shared<CData>("Complexity_Ziv_output");
}

CAlgoComplexityZiv::~CAlgoComplexityZiv()
{

}

CAlgoComplexityZiv::CAlgoComplexityZiv(const CAlgoComplexityZiv& rhs) : CAlgo(rhs)
{
	this->m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = std::dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
}

CAlgoComplexityZiv::CAlgoComplexityZiv(const std::string& class_name) : CAlgo(class_name)
{
	this->m_input = std::make_shared<CData>("Complexity_Ziv_input");
	this->m_output = std::make_shared<CData>("Complexity_Ziv_output");
}

CAlgoComplexityZiv& CAlgoComplexityZiv::operator = (const CAlgoComplexityZiv& rhs)
{
	setClassName(rhs.getClassName());

	this->m_input = std::dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = std::dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	return *this;
}

CObject* CAlgoComplexityZiv::clone() const
{
	return new CAlgoComplexityZiv(*this);
}

std::shared_ptr<CObject> CAlgoComplexityZiv::clone_shared() const
{
	return std::make_shared<CAlgoComplexityZiv>(*this);
}

bool  CAlgoComplexityZiv::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CAlgoComplexityZiv*>(ptr) != nullptr;
}

bool CAlgoComplexityZiv::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoComplexityZiv::setInputData(std::shared_ptr<CData> input_data)
{
	this->m_input = input_data;
	return true;
}

bool CAlgoComplexityZiv::execute()
{
	//calculate the threshold
	CDataSeries signal_before_binary;
	std::vector<int> signal_binary;
	int count = 0;
	m_output->getOutputData().resize(m_input->getOutputData().size());
	//calculate the signals one by one, "count" as the loop variable
	while (this->m_input->getDataSeries(count, signal_before_binary))
	{
		time_t t1 = clock();
		signal_binary.clear();
		//check if the signal have at least 2 data points
		if (signal_before_binary.size() <= 1)
		{
			//set complexity 1 and normalized complexity 0 to the output
			this->m_output->getOutputData().at(count).push_back(1);
			this->m_output->getOutputData().at(count).push_back(0);
			continue;
		}
		//calculate the mean of our signal
		float sumval = std::accumulate(std::begin(signal_before_binary), std::end(signal_before_binary), 0.0);
		float mean = sumval / signal_before_binary.size();
		//std::cout << "threshold: " << mean << std::endl;
		//calculate the symbolized signal(binary)
		for (int i = 0; i < signal_before_binary.size(); i++)
		{
			if (signal_before_binary[i] < mean)
			{
				signal_binary.push_back(0);
			}
			else
			{
				signal_binary.push_back(1);
			}
		}
		//initialize of the algorithm, the correctness has been checked and it works identically with https://pypi.org/project/Lempel-Ziv_Complexity/
		//the algorithm will be illustrated in README.md
		//TODO: the naive algorithm have a complexity of O(n^2), might not be the best one
		//60000  data points: 0.8s
		//100000 data points: 3.0s
		int c = 1;
		std::vector<int> S = { signal_binary[0] };
		std::vector<int> Q = { signal_binary[1] };
		std::vector<int> SQP = { signal_binary[0] };
		
		for (int i = 1; i < signal_binary.size(); i++)
		{
			//redundant algorithm to find if a vector is contained in another vector
			int sizeval = Q.size();
			bool foundflag = false;
			for (int j = 0; j < SQP.size() - sizeval + 1; j++)
			{
				foundflag = false;
				for (int k = 0; k < sizeval; k++)
				{
					foundflag = true;
					if (Q[k] != SQP[j + k])
					{
						foundflag = false;
						break;
					}
				}
				if (foundflag)
					break;
			}
			if (!foundflag)
			{
				if (i + 1 >= signal_binary.size())
					break;
				S.insert(S.end(), Q.begin(), Q.end());
				SQP.assign(S.begin(), S.end());
				Q.clear();
				Q.push_back(signal_binary[i + 1]);
				c += 1;
			}
			else
			{
				if (i + 1 >= signal_binary.size())
					break;
				SQP.push_back(signal_binary[i]);
				Q.push_back(signal_binary[i + 1]);
			}
		}
		if (Q.size() != 0)
		{
			c += 1;
		}
		//std::cout << "c_num: " << c << std::endl;
		this->m_output->getOutputData().at(count).push_back(c);
		float complexity_ziv = ((float)c * (log(signal_binary.size()) / log(2))) / signal_binary.size();
		this->m_output->getOutputData().at(count).push_back(complexity_ziv);
		//std::cout << "complexity after normalization is: " << complexity_ziv << std::endl;
		//std::cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << std::endl;
		count++;
	}
	
	return true;
}

std::shared_ptr<CData> CAlgoComplexityZiv::getOutputData()
{
	return this->m_output;
}

END_MAVER_EMG_NAMESPACE