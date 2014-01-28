#include "JHashTable.h"
#include "JGlobalDefine.h"

static uint32_t Primes[] = {
	53ul,         97ul,         193ul,       389ul,       769ul,
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

uint32_t nextPrime(uint32_t size)
{
	uint32_t len = sizeof(Primes) / sizeof(uint32_t);
	for(uint32_t i=0; i<len; i++)
		if(Primes[i] > size)
			return Primes[i];

	return Primes[len-1];
}

JHashTable::JHashTable() : m_nTableSize(0),
	m_nCount(0),
	m_pTable(NULL)
{

}

JHashTable::~JHashTable()
{

}

void JHashTable::Insert( const char* pKey, void* pValue )
{
	if(m_nCount >= m_nTableSize)
		Resize(m_nCount + 1);

	int nKey = MakeKey(pKey);
	Node** prev = &m_pTable[nKey % m_nTableSize];

	m_nCount++;
	Node *node = new Node;
	node->nKey= nKey;
	node->pKey= strdup(pKey);
	node->pValue = pValue;
	node->pNext = *prev;
	*prev = node;
}

void* JHashTable::Find( const char* pKey )
{
	if(m_nTableSize == 0)
		return NULL;

	int nKey = MakeKey(pKey);
	for (Node* itr = m_pTable[nKey % m_nTableSize]; itr; itr = itr->pNext)
	{
		if (itr->nKey == nKey)
		{
			if(itr->pKey != NULL && strcmp(itr->pKey, pKey) != 0)
				continue;

			return itr->pValue;
		}
	}
	return NULL;
}

int JHashTable::MakeKey( const char* pStr )
{
	int int_key = 0;

	while( *pStr )
		int_key += *pStr++;

	return int_key;
}

void JHashTable::Resize( int nSize )
{
	int currentSize = m_nTableSize;
	m_nTableSize = nextPrime(nSize);
	Node** table = new Node*[m_nTableSize];
	memset(table,0,m_nTableSize * sizeof(Node*));

	for (int i = 0; i < currentSize; i++)
	{
		for (Node* node = m_pTable[i]; node; )
		{
			//获取Key一样的节点
			Node* last = node;
			while (last->pNext && last->pNext->nKey == node->nKey)
				last = last->pNext;

			//把Key一样的连续节点移到新表
			Node** link = &table[node->nKey % m_nTableSize];
			Node* tmp = last->pNext;
			last->pNext = *link;
			*link = node;
			node = tmp;
		}
	}

	delete[] m_pTable;
	m_pTable = table;
}

