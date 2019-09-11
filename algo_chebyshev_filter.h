//Algorithm of chebyshev filter by Deng Junwei
#ifndef ALGO_CHEBYSHEV_FILTER_H
#define ALGO_CHEBYSHEV_FILTER_H

#include "algorithm.h"
#include "param_chebyshev_filter.h"
BEGIN_MAVER_EMG_NAMESPACE

class CAlgoChebyshevFilter : public CAlgo {
public:

	CAlgoChebyshevFilter();

	virtual ~CAlgoChebyshevFilter();

	CAlgoChebyshevFilter(const CAlgoChebyshevFilter& rhs);

	CAlgoChebyshevFilter(const std::string& class_name);

	CAlgoChebyshevFilter& operator = (const CAlgoChebyshevFilter& rhs);

public:

	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);

	virtual bool setParam(std::shared_ptr<CParamChebyshevFilter> input_param);

	//REQUIRE: nothing
	//MODIFIED: this->m_output
	//DESPRIPTION: do chebyshev filter
	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

private:

	std::shared_ptr<CData> m_output; // used as the output class, nothing particular, time-domain filterred signal in every place of the vector
	std::shared_ptr<CData> m_input; // used as the input class, nothing particular, time-domain signal in every palce of the vector
	std::shared_ptr<CParamChebyshevFilter> m_param; // used as the parameter class
};

END_MAVER_EMG_NAMESPACE

#endif // ALGO_CHEBYSHEV_FILTER_H

