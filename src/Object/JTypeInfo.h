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

#endif