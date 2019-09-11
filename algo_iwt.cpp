// by yuanjian 2019-4-9

#include "algo_iwt.h"
#include "dwt.h"

#include <iostream>
using namespace std;
#define    PI	3.141592653

BEGIN_MAVER_EMG_NAMESPACE

CAlgoIWT::CAlgoIWT() : CAlgo("CAlgoIWT")
{
	m_output = std::make_shared<CDataWT>();
}

CAlgoIWT::~CAlgoIWT()
{
}

CAlgoIWT::CAlgoIWT(const CAlgoIWT& rhs) : CAlgo(rhs)
{
	CAlgoIWT::operator=(rhs);
}

CAlgoIWT::CAlgoIWT(const std::string& class_name) : CAlgo(class_name)
{
	m_output = std::make_shared<CDataWT>();
}

CAlgoIWT& CAlgoIWT::operator = (const CAlgoIWT& rhs)
{
	CAlgo::operator=(rhs);
	//this->m_input = rhs.m_input;
	//this->m_output = rhs.m_output;
	//this->param = rhs.param;

	// Ó¦¸ÃÓÃ deep copy :
	this->m_input = dynamic_pointer_cast<CDataWT>(rhs.m_input->clone_shared());
	this->m_output = dynamic_pointer_cast<CData>(rhs.m_output->clone_shared());
	this->param = dynamic_pointer_cast<CParamWT>(rhs.param->clone_shared());
	return *this;
}

CObject* CAlgoIWT::clone() const
{
	return new CAlgoIWT(*this);
}

std::shared_ptr<CObject> CAlgoIWT::clone_shared() const
{
	return std::make_shared<CAlgoIWT>(*this);
}

bool CAlgoIWT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CAlgoIWT*>(ptr) != nullptr;
}

bool CAlgoIWT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoIWT::setInputData(std::shared_ptr<CData> input_data)
{
	if (dynamic_cast<CDataWT*>(input_data.get()) == nullptr) return false;
	m_input = dynamic_pointer_cast<CDataWT>(input_data);
	return true;
}

bool CAlgoIWT::setParam(std::shared_ptr<CParam> input_param)
{
	if (dynamic_cast<CParamWT*>(input_param.get()) == nullptr) return false;
	param = dynamic_pointer_cast<CParamWT>(input_param);
	return true;
}

std::shared_ptr<CData> CAlgoIWT::getOutputData()
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


bool CAlgoIWT::execute() {
#ifdef _DEBUG
	cout << endl << "Use WaveRec" << endl;
	cout << "Type: " << (param->type) << endl;
	cout << "Level: " << (param->level) << endl;
#endif // !DEBUG

	if (m_input.use_count() == 0 || m_output.use_count() == 0)
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

	vector<CDataSeries>&		out_sig= m_output->getOutputData();
	vector<CDataSeries>&		in_coef = m_input->getOutputData();
	vector<vector<int>>&		in_longs = m_input->getLongs();

	dwt.set_filters(param->type);
	for (int i = 0; i < channels; i++) {
		dwt.appcoef(out_sig[i], in_coef[i], in_longs[i], param->level);
	}
	return true;
}

END_MAVER_EMG_NAMESPACE
