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

bool JObject::SetProperty( const char *pPropertyName, const char* pValue )
{
	JClassInfo* pClass = GetClassInfo();
	if(pClass == NULL)
		return false;

	JPropertyInfo* pProp = pClass->FindProperty(pPropertyName);
	if(pProp == NULL)
		return false;
	
	pProp->SetData(this, pValue);
	return true;
}

bool JObject::GetProperty( const char *pPropertyName, char* pBuffer, int nSize )
{
	JClassInfo* pClass = GetClassInfo();
	if(pClass == NULL)
		return false;

	JPropertyInfo* pProp = pClass->FindProperty(pPropertyName);
	if(pProp == NULL)
		return false;

	pProp->GetData(this, pBuffer, nSize);
	return true;
}
