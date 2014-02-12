#ifndef JLIST_H_
#define JLIST_H_

class JList
{
	struct Node
	{
		void* data;
		Node* prev;
		Node* next;
	};

public:
	JList();
	~JList();

	void Insert(int index, void *obj);
	void Remove(int index);
	void Remove(void *obj);

	void PushBack(void *obj);

	void* First();
	const void* First() const;
	void* Next();
	const void* Next() const;
	int GetCount();

private:
	Node *m_pHead;
	Node *m_pTail;
	mutable Node *m_pWork;
	int m_nCount;
};

#endif