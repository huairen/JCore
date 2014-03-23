#ifndef JOBJECT_H_
#define JOBJECT_H_

#include "JClassInfo.h"
#include "DataType/JHashTable.h"

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

	void AddComponent(const char *name, JObject* pObj);
	void RemoveComponent(const char *name);
	JObject* GetComponent(const char *name);

protected:
	JHashTable m_Components;
};

#endif