#ifndef JTYPEINFO_H_
#define JTYPEINFO_H_

class JTypeInfo
{
public:
	JTypeInfo(int nSize, const char* pName);
	~JTypeInfo();

	virtual void SetData(void *dptr, int argc, const char **argv)=0;
	virtual const char *GetData(void *dptr)=0;

protected:
	int m_nTypeID;
	int m_nTypeSize;
	const char* m_pTypeName;
};

template <typename T>
void JStringReadValue(const T &data, char* pBuffer, int nSize);

template <typename T>
void JStringWriteValue(const char* pValue, T &data);


struct JEnumData
{
	struct Member
	{
		const char* m_pName;
		int m_nValue;
	} *m_pMembers;

	JEnumData(Member* pMember);
	int GetEnumMemberValue(const char* pName) const;
	const char* GetEnumMemberName(int nValue) const;
};

#define JENUM_TO_STRING(n,t)													\
	template<> void JStringReadValue(const t &data, char* pBuffer, int nSize)	\
	{																			\
		const char* pName = s_enumData##n.GetEnumMemberName(static_cast<int>(data));\
		if(pName != NULL)														\
			strcpy_s(pBuffer, nSize, pName);									\
	}

#define JENUM_FROM_STRING(n,t)													\
	template<> void JStringWriteValue(const char* pValue, t &data)				\
	{ data = static_cast<t>(s_enumData##n.GetEnumMemberValue(pValue));	}	


#define JBEGIN_ENUM(e)								\
	JEnumData::Member s_enumMember##e[] = {

#define JENUM_MEMBER(v) { #v, v },

#define JENUM_NAME_MEMBER(n,v) { #n, v },

#define JEND_ENUM(e)								\
		{ NULL, 0 }};								\
	JEnumData s_enumData##e(s_enumMember##e);		\
	JENUM_TO_STRING(e,e)							\
	JENUM_FROM_STRING(e,e)							\


#define JBEGIN_CLASS_ENUM(className, enumName)		\
	JEnumData::Member s_enumMember##className##enumName[] = {

#define JEND_CLASS_ENUM(c, e)						\
		{ NULL, 0 }};								\
	JEnumData s_enumData##c##e(s_enumMember##c##e);	\
	JENUM_TO_STRING(c##e,c::e)						\
	JENUM_FROM_STRING(c##e,c::e)					\

#endif