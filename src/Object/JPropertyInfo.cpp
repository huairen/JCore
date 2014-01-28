#include "JPropertyInfo.h"
#include "JClassInfo.h"

JPropertyInfo::JPropertyInfo(JClassInfo *pClass,
							 const char* pName,
							 JPropertySetter *pSetter,
							 JPropertyGetter *pGetter)
	: m_pClass(pClass)
	, m_pName(pName)
	, m_pSetter(pSetter)
	, m_pGetter(pGetter)
{
	m_pClass->AddProperty(this);
}

void JPropertyInfo::SetData( JObject* pObject, const char* pValue )
{
	if(m_pSetter)
		m_pSetter->Set(pObject, pValue);
}

void JPropertyInfo::GetData( JObject* pObject, char* pBuffer, int nSize )
{
	if(m_pGetter)
		m_pGetter->Get(pObject, pBuffer, nSize);
}
