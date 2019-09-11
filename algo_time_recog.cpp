/* algorithm of starttime recog by Junwei Deng*/

#include "algo_time_recog.h"
#include <iostream>
#include "algo_butterworth_filter.h"
BEGIN_MAVER_EMG_NAMESPACE

CAlgoTimeRecog::CAlgoTimeRecog() : CAlgo("CAlgoTimeRecog")
{
	this->m_param = std::make_shared<CParamTimeRecog>("Timerecog_param");
	this->m_input = std::make_shared<CData>("Timerecog_input");
	this->m_output = std::make_shared<CDataTimeRecog>("Timerecog_output");
}

CAlgoTimeRecog::~CAlgoTimeRecog()
{}

CAlgoTimeRecog::CAlgoTimeRecog(const CAlgoTimeRecog& rhs) : CAlgo(rhs)
{
	m_param = dynamic_pointer_cast<CParamTimeRecog>(rhs.m_param->clone_shared());
	m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	m_output = dynamic_pointer_cast<CDataTimeRecog>(rhs.m_output->clone_shared());
}

CAlgoTimeRecog::CAlgoTimeRecog(const std::string& class_name) : CAlgo(class_name)
{
	this->m_param = std::make_shared<CParamTimeRecog>("Timerecog_param");
	this->m_input = std::make_shared<CData>("Timerecog_input");
	this->m_output = std::make_shared<CDataTimeRecog>("Timerecog_output");
}

CAlgoTimeRecog& CAlgoTimeRecog::operator = (const CAlgoTimeRecog& rhs)
{
	setClassName(rhs.getClassName());

	m_param = dynamic_pointer_cast<CParamTimeRecog>(rhs.m_param->clone_shared());
	m_input = dynamic_pointer_cast<CData>(rhs.m_input->clone_shared());
	m_output = dynamic_pointer_cast<CDataTimeRecog>(rhs.m_output->clone_shared());
	return *this;
}

CObject* CAlgoTimeRecog::clone() const
{
	return new CAlgoTimeRecog(*this);
}

std::shared_ptr<CObject> CAlgoTimeRecog::clone_shared() const
{
	return std::make_shared<CAlgoTimeRecog>(*this);
}

bool  CAlgoTimeRecog::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const  CAlgoTimeRecog*>(ptr) != nullptr;
}

bool CAlgoTimeRecog::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return isSameKindAs(ptr.get());
}

bool CAlgoTimeRecog::setInputData(std::shared_ptr<CData> input_data)
{
	this->m_input = input_data;
	return true;
}

bool CAlgoTimeRecog::setParam(std::shared_ptr<CParamTimeRecog> input_param)
{
	this->m_param = input_param;
	return true;
}

bool CAlgoTimeRecog::execute()
{
	/*******************************************Butter filter for the raw data*******************************************/
	//According to the  Solnik et al. (2008): "They high-pass filtered the raw EMG before applying the TKE operator (¡°6th order, high pass filter at 20 Hz¡±)"
	
	//prepare the input data for the high-pass filter
	vector<CDataSeries>& raw_data_filter_input = this->m_input->getOutputData(); 

	//prepare the input class
	shared_ptr<CData> data_sp_rawfilter = make_shared<CData>();
	data_sp_rawfilter->setOutputData(raw_data_filter_input);

	//prepare the param class
	shared_ptr<CParamButterworthFilter> param_sp_raw = make_shared<CParamButterworthFilter>();
	param_sp_raw->setParams("highpass", this->m_param->getparam("order_raw"), true, 2*float(this->m_param->getparam("cutoff_raw"))/float(this->m_param->getparam("sampling_frequency")), "./butterworth_lowpass_corf2.txt");

	//generate the algorithm instance and set the data and param
	shared_ptr<CAlgoButterworthFilter> algo_sp_raw = make_shared<CAlgoButterworthFilter>();
	algo_sp_raw->setInputData(data_sp_rawfilter);
	algo_sp_raw->setParam(param_sp_raw);

	//execute
	algo_sp_raw->execute();

	//get the output
	this->m_input = algo_sp_raw->getOutputData();

	//prepare container for the energy signal
	int count = 0;
	CDataSeries signal_after_raw;
	CDataSeries energy_signal;
	shared_ptr<CDataTimeRecog> output_sp = make_shared<CDataTimeRecog>();
	m_output->getOutputData().resize(m_input->getOutputData().size());

	//calculate the signal one by one
	while (this->m_input->getDataSeries(count, signal_after_raw))
	{
		/********************************************Calculate the engery function*****************************************/
		//According to the Solnik et al. (2008): "The TKE operator gives a transformed signal y(n), as follows:y(n) = x(n)**2 - x(n-1)*x(n-2)"
		//resize the energy_signal
		energy_signal.resize(signal_after_raw.size());
		//calculate the energy signal
		energy_signal[0] = signal_after_raw[0];
		energy_signal[signal_after_raw.size() - 1] = signal_after_raw[signal_after_raw.size() - 1];
		for (int i = 1; i < signal_after_raw.size() - 1; i++)
		{
			energy_signal[i] = signal_after_raw[i] * signal_after_raw[i] - signal_after_raw[i - 1] * signal_after_raw[i + 1];
		}
		/********************************************filter the engery function*****************************************/
		//butter filter the energy signal, same structure as the above filter
		//According to the Solnik et al. (2008): They low-pass filtered the TKE signal y(n)(¡°6th order, zero-phase lowpass filter at 50 Hz¡±) before threshold detection
		vector<CDataSeries> filter_input;
		filter_input.push_back(energy_signal);
		shared_ptr<CData> data_sp = make_shared<CData>();
		data_sp->setOutputData(filter_input);
		shared_ptr<CParamButterworthFilter> param_sp = make_shared<CParamButterworthFilter>();
		param_sp->setParams("lowpass", this->m_param->getparam("order_TKE"), true, 2 * float(this->m_param->getparam("cutoff_TKE")) / float(this->m_param->getparam("sampling_frequency")), "./butterworth_lowpass_corf.txt");//param
		shared_ptr<CAlgoButterworthFilter> algo_sp = make_shared<CAlgoButterworthFilter>();
		algo_sp->setInputData(data_sp);
		algo_sp->setParam(param_sp);
		algo_sp->execute();
		CDataSeries result_CDS = algo_sp->getOutputData()->getOutputData().at(0);

		/********************************************find all the starttime and endtime*****************************************/
		//According to the Solnik et al. (2008):  threshold crossing was defined as the first point to cross the threshold and stay above threshold for 25 or more samples, at a 1 kHz sampling rate.
		int start = 0;
		int end = 0;
		int count_num = 0;
		float threshold = (this->m_param->quiet_mean + this->m_param->getparam("J")*this->m_param->quiet_std);
		while (true)
		{
			count_num = 0;
			for (int i = end; i < result_CDS.size(); i++)
			{
				if (count_num >= this->m_param->getparam("windows_width"))
				{
					break;
				}
				if (result_CDS[i] > threshold)
				{
					count_num++;
				}
				else
				{
					count_num = 0;
					start = i;
				}
			}
			if (start >= result_CDS.size() - 25) break;
			this->m_output->getOutputData().at(count).push_back(float(start));
			count_num = 0;
			for (int i = start; i < result_CDS.size(); i++)
			{
				if (count_num >= this->m_param->getparam("windows_width"))
				{
					break;
				}
				if (result_CDS[i] < threshold)
				{
					count_num++;
				}
				else
				{
					count_num = 0;
					end = i;
				}
			}
			this->m_output->getOutputData().at(count).push_back(float(end));
			if (end >= result_CDS.size() - 30) break;
		}
		count++;
	}
	
	return true;
}

std::shared_ptr<CData> CAlgoTimeRecog::getOutputData()
{
	return this->m_output;
}

END_MAVER_EMG_NAMESPACE