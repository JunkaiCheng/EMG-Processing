//base object by maanbang 2019-3-31

#ifndef _MAVER_EMG_ALGO_OBJECT_H_
#define _MAVER_EMG_ALGO_OBJECT_H_

#include <string>
#include <memory>

#define BEGIN_MAVER_EMG_NAMESPACE namespace MaverEMG {
#define END_MAVER_EMG_NAMESPACE }

BEGIN_MAVER_EMG_NAMESPACE

class CObject
{
public:
	CObject();

	CObject(const CObject& rhs);

	CObject(const std::string& class_name);

	CObject& operator = (const CObject& rhs);

	virtual ~CObject();

public:
	void setClassName(const std::string& class_name);

	std::string getClassName() const;

	virtual CObject* clone() const;

	virtual std::shared_ptr<CObject> clone_shared() const;

	virtual bool isSameKindAs(const CObject* ptr);

	virtual bool isSameKindAs(const std::shared_ptr<CObject> ptr);

private:
	std::string m_className;

};

END_MAVER_EMG_NAMESPACE

#endif