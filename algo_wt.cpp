// by yuanjian 2019-4-9

#include "algo_wt.h"
#include "dwt.h"

#include <iostream>
using namespace std;
#define    PI	3.141592653

BEGIN_MAVER_EMG_NAMESPACE

CAlgoWT::CAlgoWT() : CAlgo("CAlgoWT")
{
	m_output = std::make_shared<CDataWT>();
}

CAlgoWT::~CAlgoWT()
{
}

CAlgoWT::CAlgoWT(const CAlgoWT& rhs) : CAlgo(rhs)
{
	CAlgoWT::operator=(rhs);
}

CAlgoWT::CAlgoWT(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CDataWT>();
}

CAlgoWT& CAlgoWT::operator = (const CAlgoWT& rhs)
{
	CAlgo::operator=(rhs);
	//this->m_input		= rhs.m_input;
	//this->m_output	= rhs.m_output;
	//this->param		= rhs.param;

	// Ó¦¸ÃÓÃ deep copy :
	this->m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CDataWT>(rhs.m_output->clone_shared());
	this->param = dynamic_pointer_cast<CParamWT>(rhs.param->clone_shared());
	return *this;
}

CObject* CAlgoWT::clone() const
{
	return new CAlgoWT(*this);
}

std::shared_ptr<CObject> CAlgoWT::clone_shared() const
{
	return std::make_shared<CAlgoWT>(*this);
}

bool CAlgoWT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoWT*>(ptr) != nullptr;
}

bool CAlgoWT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoWT::setInputData(std::shared_ptr<CData> input_data)
{
	m_input = input_data;
	return true;
}

bool CAlgoWT::setParam(std::shared_ptr<CParam> input_param)
{
	if (dynamic_cast<CParamWT*>(input_param.get()) == nullptr) return false;
	param = dynamic_pointer_cast<CParamWT>(input_param);
	return true;
}

std::shared_ptr<CData> CAlgoWT::getOutputData()
{
	return m_output;
}

// -- EXECUTE --

inline static
void print_vec(vector<float> &v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}cout << endl;
}


bool CAlgoWT::execute() {
#ifdef _DEBUG
	cout << endl << "Use WaveDec" << endl;
	cout << "Type: " << (param->type) << endl;
	cout << "Level: " << (param->level) << endl;
#endif // !DEBUG

	if (m_input.use_count() == 0 || m_output.use_count()==0)
		return false;
	if (param.use_count() == 0)
		return false;

	size_t channels = m_input->getOutputData().size();
	size_t datalength = m_input->getOutputData()[0].size();

	if (datalength <= 2)
		return false;

	for (size_t i = 0; i < channels; i++)
	{
		if (datalength != m_input->getOutputData()[i].size())
			return false;
	}

	m_output->resizeOutputData(channels);
	m_output->resizeLongs(channels);

	vector<CDataSeries>&		out_coef = m_output ->getOutputData();
	vector<vector<int>>&		out_longs = m_output->getLongs();


	dwt.set_filters(param->type);
	for (int i = 0; i < channels; i++) {
		CDataSeries		src_data;
		m_input->getDataSeries(i, src_data);
		dwt.wavedec(out_coef[i], out_longs[i], src_data, param->level);
	}

	return true;
}

END_MAVER_EMG_NAMESPACE
