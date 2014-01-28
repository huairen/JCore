#ifndef JARRAY_H_
#define JARRAY_H_

#define JARRAY_BLOCK_SIZE 16

class JArray
{
public:
	JArray(int nTypeSize);
	~JArray();

	void Insert(int index, void *obj);
	void Remove(int index);

	void PushBack(void *obj);
	void* PopBack();

	void* First();
	void* Next();
	int GetCount();

protected:
	bool Resize(int nSize);

private:
	int m_nTypeSize;
	int m_nArraySize;
	int m_nCount;
	void* m_pBuffer;
};

#endif