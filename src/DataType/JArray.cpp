#include "JArray.h"
#include "JGlobalDefine.h"

JArray::JArray(int nTypeSize) : m_nTypeSize(nTypeSize),
	m_nArraySize(0), m_nCount(0), m_pBuffer(0)
{
}

JArray::~JArray()
{
	free(m_pBuffer);
}

void JArray::Insert( int index, void *obj )
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);

	memcpy(((char*)m_pBuffer + (index * m_nTypeSize)), obj, m_nTypeSize);
	m_nCount++;
}

void JArray::Remove( int index )
{
	if (index < (m_nCount - 1))
	{
		memmove(((char*)m_pBuffer + (index * m_nTypeSize)),
			((char*)m_pBuffer + ((index + 1) * m_nTypeSize)),
			(m_nCount - index - 1) * m_nTypeSize);
	}

	m_nCount--;
}

void JArray::PushBack( void* obj )
{
	Insert(m_nCount, obj);
}

void* JArray::PopBack()
{
	m_nCount--;
	return ((char*)m_pBuffer + (m_nCount * m_nTypeSize));
}

void* JArray::At(int index)
{
	if(index >= m_nCount)
		return NULL;

	return ((char*)m_pBuffer + (index * m_nTypeSize));;
}

bool JArray::Resize( int nSize )
{
	if (nSize > 0)
	{
		int blocks = nSize / JARRAY_BLOCK_SIZE;
		if (nSize % JARRAY_BLOCK_SIZE)
			blocks++;
		int mem_size = blocks * JARRAY_BLOCK_SIZE * m_nTypeSize;
		m_pBuffer = m_pBuffer ? realloc(m_pBuffer,mem_size) :
			malloc(mem_size);

		m_nArraySize = blocks * JARRAY_BLOCK_SIZE;
		return true;
	}

	if (m_pBuffer) 
	{
		free(m_pBuffer);
		m_pBuffer = 0;
	}

	m_nArraySize = 0;
	m_nCount = 0;
	return true;
}
