#include "JObject.h"
#include "JGlobalDefine.h"

JClassInfo JObject::ms_classInfo("JObject",NULL,NULL);
JClassInfo *JObject::GetClassInfo() const
{ return &JObject::ms_classInfo; }

JObject::JObject()
{
}

JObject::~JObject()
{
}

JPropertyInfo* JObject::FindProperty(const char *pPropertyName)
{
	JClassInfo* pClass = GetClassInfo();
	if(pClass != NULL)
	{
		JPropertyInfo* pProp = pClass->FindProperty(pPropertyName);
		if(pProp != NULL)
			return pProp;
	}
	
	return NULL;
}

bool JObject::SetProperty( const char *pPropertyName, const char* pValue )
{
	JPropertyInfo* pProp = FindProperty(pPropertyName);
	if(pProp != NULL)
		return pProp->SetData(this, pValue);

	JHashTable::Iterator it = m_Components.Begin();
	for (; !it.IsEnd(); ++it)
	{
		JObject* pObj = (JObject*)it.GetVaule();
		if(pObj != NULL && pObj->SetProperty(pPropertyName, pValue))
			return true;
	}

	return false;
}

bool JObject::GetProperty( const char *pPropertyName, char* pBuffer, int nSize )
{
	JPropertyInfo* pProp = FindProperty(pPropertyName);
	if(pProp != NULL)
		return pProp->GetData(this, pBuffer, nSize);

	JHashTable::Iterator it = m_Components.Begin();
	for (; !it.IsEnd(); ++it)
	{
		JObject* pObj = (JObject*)it.GetVaule();
		if(pObj != NULL && pObj->GetProperty(pPropertyName, pBuffer, nSize))
			return true;
	}

	return false;
}

void JObject::CopyProperty(JObject* pParent)
{
	char szBuff[1024];
	JClassInfo* pClassThis = GetClassInfo();
	JClassInfo* pClassParent = pParent->GetClassInfo();

	while(pClassParent != NULL && pClassThis != NULL)
	{
		if(pClassParent == pClassThis)
		{
			const JList& list = pClassParent->GetPropertyList();
			const JPropertyInfo* pProp = (const JPropertyInfo*)list.First();
			while(pProp != NULL)
			{
				if(pProp->GetData(pParent, szBuff, sizeof(szBuff)))
					SetProperty(pProp->GetName(), szBuff);

				pProp = (const JPropertyInfo*)list.Next();
			}

			pClassParent = pClassParent->GetParentClass();
		}

		pClassThis = pClassThis->GetParentClass();
	}
}

JObject* JObject::Clone()
{
	JObject* pObj = GetClassInfo()->CreateObject();
	if(pObj != NULL)
	{
		pObj->CopyProperty(this);
		return pObj;
	}

	return NULL;
}

void JObject::AddComponent(const char *name, JObject* pObj)
{
	m_Components.Insert(name, pObj);
}

void JObject::RemoveComponent(const char *name)
{
	JObject* pObj = (JObject*)m_Components.Remove(name);
	delete pObj;
}

JObject* JObject::GetComponent(const char *name)
{
	return (JObject*)m_Components.Find(name);
}
