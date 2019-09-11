/* algorithm of Lempel-ziv complexity by Junwei Deng*/

#ifndef __ALGO_COMPLEXITY_ZIV_H
#define __ALGO_COMPLEXITY_ZIV_H

#include "object.h"
#include "data.h"
#include "param.h"
#include "algorithm.h"

BEGIN_MAVER_EMG_NAMESPACE

class CAlgoComplexityZiv : public CAlgo {
public:

	CAlgoComplexityZiv();

	virtual ~CAlgoComplexityZiv();

	CAlgoComplexityZiv(const CAlgoComplexityZiv& rhs);

	CAlgoComplexityZiv(const std::string& class_name);

	CAlgoComplexityZiv& operator = (const CAlgoComplexityZiv& rhs);

public:

	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	virtual bool setInputData(std::shared_ptr<CData> input_data);
	
	//REQUIRE: the signal inputted should have at least 1 data points, although the function will return 1 for only zero-data-point signal, it may cause confusion
	//MODIFIED: this->m_input, this->m_output
	//DESPRIPTION: find the number of "pattern" in this series of signal, and set the complexity and normalizaed-complexity for each signal
	virtual bool execute();

	virtual std::shared_ptr<CData> getOutputData();

private:

	std::shared_ptr<CData> m_output; // used as the output class, specific detail will be illustrated in readme.md
	std::shared_ptr<CData> m_input; // used as the input class, nothing particular, time-domain signal in every palce of the vector

};

END_MAVER_EMG_NAMESPACE
#endif
