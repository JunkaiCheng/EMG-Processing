#ifndef _MAVOR_EMG_PARAM_FDA_H_
#define _MAVOR_EMG_PARAM_FDA_H_

#include "param.h"
#include <string>
#include <vector>

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

class CParamFDA : public CParam
{
public:
	CParamFDA();

	virtual ~CParamFDA();

	CParamFDA(const CParamFDA& rhs);

	CParamFDA(const std::string& class_name);

	CParamFDA& operator = (const CParamFDA& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

	// -----------------------------------------------------------------------------------
	// ���������Ϣ
	// -----------------------------------------------------------------------------------

public:
	bool		setParams(string type_in, float freq_in);
public:
	string	type;		//Ƶ���������
	//	��Ч���룺
	//			ƽ��Ƶ��MNF/ƽ��Ƶ��Ƶ��MSF/����Ƶ��CF/ƽ������Ƶ��MPF		eg:"MNF"
	//			��λƵ�� MF/MDF
	//			�������ܶ�PSD
	//			Ƶ�����SPA
	float		freq;		//����Ƶ��
};

END_MAVER_EMG_NAMESPACE
#endif