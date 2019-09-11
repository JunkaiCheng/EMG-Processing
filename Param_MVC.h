//mvc param class by hebaoxiang 2019-04-02
#ifndef _MAVER_EMG_PARAM_MVC_H_
#define _MAVER_EMG_PARAM_MVC_H_

#include "param.h"
BEGIN_MAVER_EMG_NAMESPACE
class CParam_MVC : public CParam
{
public:
	CParam_MVC();
	~CParam_MVC();

	CParam_MVC(const CParam_MVC& rhs);

	CParam_MVC(const std::string& class_name);

	CParam_MVC& operator = (const CParam_MVC& rhs);

public:
	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);
	void   Set_MVCMethod(std::string& method);
	std::string    Get_MVCMethod();
private:
	std::string my_method;
};
END_MAVER_EMG_NAMESPACE
#endif

