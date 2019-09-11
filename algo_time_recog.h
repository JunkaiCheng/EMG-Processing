/* algorithm of starttime recog by Junwei Deng*/

#ifndef __MAVER_EMG_ALGO_EMG_TIME_ALGO_H
#define __MAVER_EMG_ALGO_EMG_TIME_ALGO_H

#include "object.h"
#include "data.h"
#include "param.h"
#include "algorithm.h"
#include "data_time_recog.h"
#include "param_time_recog.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoTimeRecog : public CAlgo {
public:

	CAlgoTimeRecog();

	virtual ~CAlgoTimeRecog();

	CAlgoTimeRecog(const CAlgoTimeRecog& rhs);

	CAlgoTimeRecog(const std::string& class_name);

	CAlgoTimeRecog& operator = (const CAlgoTimeRecog& rhs);

public:

	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	bool setParam(std::shared_ptr<CParamTimeRecog> input_param);

	//MODIFIED: this->m_input, this->m_output
	//DESCRIPTION: this function find all the starttime and endtime in all the input signals, for more detailed information, refer to the README.md
	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

private:

	std::shared_ptr<CData> m_input; // used as the input time-domain signal
	std::shared_ptr<CDataTimeRecog> m_output; // used as the output (starttime for the input signal)
	std::shared_ptr<CParamTimeRecog> m_param; //used as the parameter of the algorithm

};


END_MAVER_EMG_NAMESPACE

#endif // !__MAVER_EMG_ALGO_EMG_TIME_ALGO_H
