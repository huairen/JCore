#include "JObject.h"
#include "JGlobalDefine.h"

void RefCounter::DecRef()
{
	if ( --m_nCount == 0 )
		delete this;
}

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
	if(pProp == NULL)
		return false;
	return pProp->SetData(this, pValue);
}

bool JObject::GetProperty( const char *pPropertyName, char* pBuffer, int nSize )
{
	JPropertyInfo* pProp = FindProperty(pPropertyName);
	if(pProp == NULL)
		return false;
	return pProp->GetData(this, pBuffer, nSize);
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
