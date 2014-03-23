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
	class Iterator
	{
	public:
		Iterator(Node** pTable, int );
		JHashTable::Iterator& operator ++();
		JHashTable::Iterator operator ++(int);

		bool IsEnd() const;
		void *GetVaule() const;

	private:
		Node* pPointer;
		Node** pCurr;
		Node** pEnd;
	};

public:
	JHashTable();
	~JHashTable();

	void Insert(const char* pKey, void* pValue);
	void* Remove(const char* pKey);
	void* Find(const char* pKey);

	Iterator Begin();

protected:
	int MakeKey(const char* pStr);
	void Resize(int nSize);

private:
	int m_nTableSize;
	int m_nCount;
	Node** m_pTable;
};

#endif