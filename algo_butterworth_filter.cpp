
// 导入库
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <vector>
#include <math.h>
#include "algo_butterworth_filter.h"
#include "data_butterworth_filter.h"
#include "param_butterworth_filter.h"

#define M_PI 3.1415926

BEGIN_MAVER_EMG_NAMESPACE

CAlgoButterworthFilter::CAlgoButterworthFilter(): CAlgo("CAlgoButterworthFilter")
{
	m_output = make_shared<CDataButterworthFilter>("CDataButterworthFilter");
}

CAlgoButterworthFilter::~CAlgoButterworthFilter()
{
}

CAlgoButterworthFilter::CAlgoButterworthFilter(const CAlgoButterworthFilter& rhs): CAlgo(rhs)
{
	CAlgoButterworthFilter::operator=(rhs);
}

CAlgoButterworthFilter::CAlgoButterworthFilter(const std::string& class_name): CAlgo(class_name)
{
	m_output = make_shared<CDataButterworthFilter>("CDataButterworthFilter");
}

CAlgoButterworthFilter& CAlgoButterworthFilter::operator = (const CAlgoButterworthFilter& rhs)
{
	CAlgo::operator=(rhs);

	m_param		= dynamic_pointer_cast<CParamButterworthFilter>(rhs.m_param->clone_shared());
	m_input		= dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	m_output	= dynamic_pointer_cast<CDataButterworthFilter>(rhs.m_output->clone_shared());

	return *this;
}

CObject* CAlgoButterworthFilter::clone() const
{
	return new CAlgoButterworthFilter(*this);
}

std::shared_ptr<CObject> CAlgoButterworthFilter::clone_shared() const
{
	return std::make_shared<CAlgoButterworthFilter>(*this);
}

bool CAlgoButterworthFilter::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoButterworthFilter*>(ptr) != nullptr;
}

bool CAlgoButterworthFilter::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoButterworthFilter::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoButterworthFilter::setParam(std::shared_ptr<CParam> input_param)
{
	m_param = dynamic_pointer_cast<CParamButterworthFilter>(input_param);
	return true;
}

bool CAlgoButterworthFilter::execute()
{
	// 为输出分配空间
	m_output->getOutputData().resize(m_input->getOutputData().size());

	// 对每一个channel做处理
	for (size_t k = 0; k < m_input->getOutputData().size(); k++)
	{
		int nc = m_param->ccof.size();
		int nd = m_param->dcof.size();
		int nx = m_input->getOutputData().at(k).size();
		int ny = nx + nc;

		for (int i = 0; i < ny; ++i)
		{
			double s1 = 0.0;

			for (int j = (i < nd ? 0 : i - nd + 1); j < i; ++j)
				s1 += m_param->dcof.at(i - j) * m_output->getOutputData().at(k).at(j);

			double s2 = 0.0;

			for (int j = (i < nc ? 0 : i - nc + 1); j <= (i<nx ? i : nx - 1); ++j)
				s2 += m_param->ccof.at(i - j) * m_input->getOutputData().at(k).at(j);

			m_output->getOutputData().at(k).push_back(s2 - s1);
		}
	}

}

std::shared_ptr<CData> CAlgoButterworthFilter::getOutputData()
{
	return m_output;
}

END_MAVER_EMG_NAMESPACE

