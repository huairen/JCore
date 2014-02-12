#ifndef JOBJECT_H_
#define JOBJECT_H_

#include "JClassInfo.h"

class RefCounter
{
public:
	RefCounter() { m_nCount = 1; }

	int GetRefCount() const { return m_nCount; }

	void IncRef() { m_nCount++; }
	void DecRef();

protected:
	virtual ~RefCounter() {}

private:
	int m_nCount;
};

class JObject
{
	JDECLARE_ABSTRACT_CLASS(JObject)

public:
	JObject();
	virtual ~JObject();

	JPropertyInfo* FindProperty(const char *pPropertyName);

	bool SetProperty(const char *pPropertyName, const char* pValue);
	bool GetProperty (const char *pPropertyName, char* pBuffer, int nSize);
	void CopyProperty(JObject* pParent);

	JObject* Clone();

private:
};

#endif