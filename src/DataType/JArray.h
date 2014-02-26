#ifndef JARRAY_H_
#define JARRAY_H_

#define JARRAY_BLOCK_SIZE 16

template<typename T>
class JArray
{
public:
	JArray();
	~JArray();

	void Insert(int index, const T& obj);
	void Remove(int index);

	void PushBack(const T& obj);
	T &PopBack();

	void Increment();
	void IncrementAt(int index);

	T &First();
	T &Last();
	T &At(int index);

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
JArray<T>::JArray()
	: m_nArraySize(0)
	, m_nCount(0)
	, m_pBuffer(0)
{
}

template<typename T>
JArray<T>::~JArray()
{
	delete[] m_pBuffer;
}

template<typename T>
void JArray<T>::Insert( int index, const T &obj )
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);

	m_pBuffer[index] = obj;
	m_nCount++;
}

template<typename T>
void JArray<T>::Remove( int index )
{
	if (index < (m_nCount - 1))
	{
		T* ptr = m_pBuffer + index;
		memmove(ptr, ptr + 1, (m_nCount - index - 1)*sizeof(T));
	}

	m_nCount--;
}

template<typename T>
void JArray<T>::PushBack( const T &obj )
{
	Insert(m_nCount, obj);
}

template<typename T>
T & JArray<T>::PopBack()
{
	m_nCount--;
	return m_pBuffer[m_nCount];
}

template<typename T>
void JArray<T>::Increment()
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);

	m_nCount++;
}

template<typename T>
void JArray<T>::IncrementAt(int index)
{
	if(m_nCount >= m_nArraySize)
		Resize(m_nCount + 1);

	m_nCount++;
}

template<typename T>
inline T & JArray<T>::First()
{
	return m_pBuffer[0];
}

template<typename T>
inline T & JArray<T>::Last()
{
	return m_pBuffer[m_nCount-1];
}

template<typename T>
T & JArray<T>::At(int index)
{
	return m_pBuffer[index];
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