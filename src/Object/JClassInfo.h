#ifndef JRTTI_H_
#define JRTTI_H_

#include "DataType/JHashTable.h"
#include "DataType/JList.h"
#include "JPropertyInfo.h"

class JObject;
typedef JObject *(*JObjectConstructorFn)(void);

class JClassInfo
{
public:
	JClassInfo( const char *pName,
				JClassInfo *pParent,
				JObjectConstructorFn ctor);

	~JClassInfo();

	JObject *CreateObject() const;
	void AddProperty(JPropertyInfo *pProp);
	JPropertyInfo* FindProperty(const char* pPropertyName);

	static JClassInfo *FindClass(const char* pClassName);

private:
	void Register();

private:
	const char *m_pName;
	JClassInfo *m_pParentClass;
	JObjectConstructorFn m_pObjectConsturctor;

	JList m_Properties;

	static JHashTable *sm_pClassTable;
};

JObject *JCreateDynamicObject(const char* name);

//declare
#define JDECLARE_ABSTRACT_CLASS(name)								\
	public:															\
		static JClassInfo ms_classInfo;								\
		virtual JClassInfo *GetClassInfo() const;


#define JDECLARE_DYNAMIC_CLASS(name)								\
	JDECLARE_ABSTRACT_CLASS(name);									\
	static JObject* CreateObject();

//implement
#define JIMPLEMENT_CLASS_COMMON(name, basename, func)				\
	JClassInfo name::ms_classInfo(#name,							\
			&basename::ms_classInfo,								\
			func);													\
																	\
	JClassInfo *name::GetClassInfo() const							\
		{ return &name::ms_classInfo; }


#define JIMPLEMENT_DYNAMIC_CLASS(name, basename)					\
	JIMPLEMENT_CLASS_COMMON(name, basename, name::CreateObject)		\
	JObject* name::CreateObject()									\
		{ return new name; }

#define JFORCE_LINK_OBJ(name)										\
	int ForceLink##name();											\
	const int ForceLinkVar##name = ForceLink##name();

#define JIMPLEMENT_FORCE_LINK_OBJ(name)								\
	int ForceLink##name()											\
		{ return 0; }
#endif