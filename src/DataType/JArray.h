#ifndef JARRAY_H_
#define JARRAY_H_

#define JARRAY_BLOCK_SIZE 16

template<typename T>
class JArray
{
public:
	// type definitions
	typedef T              value_type;
	typedef T*             iterator;
	typedef const T*       const_iterator;
	typedef T&             reference;
	typedef const T&       const_reference;

public:
	JArray(): m_nArraySize(0), m_nCount(0), m_pBuffer(0) {}
	~JArray() { delete[] m_pBuffer; }

	void Insert(int index, const_reference obj);
	void Remove(int index);
	void Increment();

	inline void PushBack(const_reference obj) { Insert(m_nCount, obj); }
	inline reference PopBack() { return m_pBuffer[--m_nCount]; }


	inline reference First() { return m_pBuffer[0]; }
	inline reference Last() { return m_pBuffer[m_nCount-1]; }
	inline reference At(int index) { return m_pBuffer[index]; }

	inline int GetCount() { return m_nCount; }
	inline bool IsEmpty() { return m_nCount==0; }

protected:
	bool Resize(int nSize);

private:
	int m_nArraySize;
	int m_nCount;
	T* m_pBuffer;
};


template<typename T>
void JArray<T>::Insert(int index, const_reference obj)
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);

	m_pBuffer[index] = obj;
	m_nCount++;
}

template<typename T>
void JArray<T>::Remove(int index)
{
	if (index < (m_nCount - 1))
	{
		T* ptr = m_pBuffer + index;
		memmove(ptr, ptr + 1, (m_nCount - index - 1)*sizeof(T));
	}

	m_nCount--;
}

template<typename T>
void JArray<T>::Increment()
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);
	m_nCount++;
}

template<typename T>
bool JArray<T>::Resize( int nSize )
{
	if (nSize > 0)
	{
		int blocks = nSize / JARRAY_BLOCK_SIZE;
		if (nSize % JARRAY_BLOCK_SIZE)
			blocks++;
		m_nArraySize = blocks * JARRAY_BLOCK_SIZE;

		if(m_pBuffer != NULL)
		{
			T* ptr = new T[m_nArraySize];
			if(ptr != NULL && m_nCount > 0)
				memcpy(ptr,m_pBuffer,m_nCount*sizeof(T));
			delete[] m_pBuffer;
			m_pBuffer = ptr;
		}
		else
		{
			m_pBuffer = new T[m_nArraySize];
		}
	}

	return (m_pBuffer != NULL);
}

#endif