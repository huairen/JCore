#include "JTypeInfo.h"
#include "JGlobalDefine.h"
#include "math/JPoint.h"

int g_nTypeCount = 0;

JTypeInfo::JTypeInfo(int nSize, const char* pName) : m_nTypeSize(nSize),
	m_pTypeName(pName)
{
	m_nTypeID = g_nTypeCount++;
}

JTypeInfo::~JTypeInfo()
{

}


JEnumData::JEnumData(Member* pMember)
{
	m_pMembers = pMember;
}

int JEnumData::GetEnumMemberValue(const char* pName) const
{
	for (int i = 0; m_pMembers[i].m_pName; i++)
		if(stricmp(pName, m_pMembers[i].m_pName) == 0)
			return m_pMembers[i].m_nValue;

	return 0;
}

const char* JEnumData::GetEnumMemberName(int nValue) const
{
	for (int i = 0; m_pMembers[i].m_pName; i++)
		if(m_pMembers[i].m_nValue == nValue)
			return m_pMembers[i].m_pName;

	return NULL;
}


template<> void JStringReadValue(const bool &data, char* pBuffer, int nSize)
{
	if(data)
		strcpy_s(pBuffer, nSize, "true");
	else
		strcpy_s(pBuffer, nSize, "false");
}
template<> void JStringWriteValue(const char* pValue, bool &data)
{
	if(!strnicmp(pValue, "true", 4) || atoi(pValue))
		data = true;
	else
		data = false;
}

template<> void JStringReadValue(const int &data, char* pBuffer, int nSize)
{
	sprintf_s(pBuffer, nSize, "%d", data);
}
template<> void JStringWriteValue(const char* pValue, int &data)
{
	sscanf_s(pValue, "%d", &data);
}


template<> void JStringReadValue(const JPoint2I &data, char* pBuffer, int nSize)
{
	sprintf_s(pBuffer, nSize, "%d,%d", data.x, data.y);
}
template<> void JStringWriteValue(const char* pValue, JPoint2I &data)
{
	sscanf_s(pValue, "%d,%d", &data.x, &data.y);
}


template<> void JStringReadValue(const std::string &data, char* pBuffer, int nSize)
{
}
template<> void JStringWriteValue(const char* pValue, std::string &data)
{
	data = pValue;
}