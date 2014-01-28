#ifndef JHASHTABLE_H_
#define JHASHTABLE_H_

class JHashTable
{
	struct Node
	{
		int nKey;
		const char* pKey;
		void* pValue;
		Node *pNext;
	};

public:
	JHashTable();
	~JHashTable();

	void Insert(const char* pKey, void* pValue);

	void* Find(const char* pKey);

protected:
	int MakeKey(const char* pStr);
	void Resize(int nSize);

private:
	int m_nTableSize;
	int m_nCount;
	Node** m_pTable;
};

#endif