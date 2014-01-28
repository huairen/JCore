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
	void* Next();
	int GetCount();

private:
	Node *m_pHead;
	Node *m_pTail;
	Node *m_pWork;
	int m_nCount;
};

#endif