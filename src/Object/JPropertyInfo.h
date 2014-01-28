#ifndef JPROPERTYINFO_H_
#define JPROPERTYINFO_H_

#include "JTypeInfo.h"

class JObject;
class JClassInfo;

class JPropertySetter
{
public:
	virtual void Set( JObject *object, const char* pValue ) const = 0;
};

class JPropertyGetter
{
public:
	virtual void Get( const JObject *object, char* pBuffer, int nSize) const = 0;
};

class JPropertyInfo
{
public:
	JPropertyInfo(JClassInfo *pClass,
				  const char* pName,
				  JPropertySetter *pSetter,
				  JPropertyGetter *pGetter);

	void SetData(JObject* pObject, const char* pValue);
	void GetData(JObject* pObject, char* pBuffer, int nSize);

	inline const char* GetName()
	{ return m_pName; }

private:
	const char* m_pName;
	JClassInfo* m_pClass;
	JPropertySetter* m_pSetter;
	JPropertyGetter* m_pGetter;
};

#define JPROPERTY_SETTER( property, Klass, valueType, setterMethod )		\
	class JPropertySetter##property : public JPropertySetter				\
	{                                                                       \
	public:																	\
		void Set( JObject *object, const char* pValue ) const				\
		{                                                                   \
			Klass *obj = dynamic_cast<Klass*>(object);						\
			valueType tempobj;												\
			JStringWriteValue(pValue, tempobj);								\
			obj->setterMethod(tempobj);										\
		}                                                                   \
	};

#define JPROPERTY_GETTER( property, Klass, valueType, gettermethod )		\
	class JPropertyGetter##property : public JPropertyGetter				\
	{                                                                       \
	public:                                                                 \
		void Get( const JObject *object, char* pBuffer, int nSize) const	\
		{                                                                   \
			const Klass *obj = dynamic_cast<const Klass*>(object);          \
			const valueType& result = obj->gettermethod();					\
			JStringReadValue(result, pBuffer, nSize);						\
		}                                                                   \
	};

#define JCLASS_PROPERTY(clsName, property, type, setterMethod, getterMethod)\
	JPROPERTY_SETTER(property, clsName, type, setterMethod)					\
	static JPropertySetter##property clsName##property##setter;				\
	JPROPERTY_GETTER(property, clsName, type, getterMethod)					\
	static JPropertyGetter##property clsName##property##getter;				\
	static JPropertyInfo clsName##property(&clsName::ms_classInfo,			\
				#property, &clsName##property##setter,						\
				&clsName##property##getter);

#define JCLASS_WRITEONLY_PROPERTY(clsName, property, type, setterMethod)	\
	JPROPERTY_SETTER(property, clsName, type, setterMethod)					\
	static JPropertySetter##property clsName##property##setter;				\
	static JPropertyInfo clsName##property(&clsName::ms_classInfo,			\
				#property, &clsName##property##setter, NULL);

#endif