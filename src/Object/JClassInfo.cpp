#include "JClassInfo.h"
#include "JGlobalDefine.h"

JHashTable* JClassInfo::sm_pClassTable = NULL;

JClassInfo::JClassInfo( const char *pName, JClassInfo *pParent, JObjectConstructorFn ctor )
	: m_pName(pName)
	, m_pParentClass(pParent)
	, m_pObjectConsturctor(ctor)
{
	Register();
}

JClassInfo::~JClassInfo()
{

}

JObject * JClassInfo::CreateObject() const
{
	return m_pObjectConsturctor ? (*m_pObjectConsturctor)() : 0;
}

void JClassInfo::AddProperty( JPropertyInfo *pProp )
{
	m_Properties.PushBack(pProp);
}

JPropertyInfo* JClassInfo::FindProperty( const char* pPropertyName )
{
	JPropertyInfo* pProp = (JPropertyInfo*)m_Properties.First();
	while(pProp)
	{
		if(stricmp(pPropertyName, pProp->GetName()) == 0)
			return pProp;
		pProp = (JPropertyInfo*)m_Properties.Next();
	}

	if(m_pParentClass != NULL)
		return m_pParentClass->FindProperty(pPropertyName);

	return NULL;
}

JClassInfo * JClassInfo::FindClass( const char* pClassName )
{
	return (JClassInfo*)sm_pClassTable->Find(pClassName);
}

void JClassInfo::Register()
{
	if(!sm_pClassTable)
		sm_pClassTable = new JHashTable;

	if(sm_pClassTable)
		sm_pClassTable->Insert(m_pName, this);
}

JObject * JCreateDynamicObject( const char* name )
{
	JClassInfo* pClass = JClassInfo::FindClass(name);
	if(pClass != 0)
		return pClass->CreateObject();
	return 0;
}