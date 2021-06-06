#ifndef __LIST2
#define __LIST2

#include <iostream>
#include <stack>
#include "Node2.h"


template<class K, class V>
class SkipList
{
private:
	double listProb;

public:
	int maxLevel;
	IndexNode<K, V>* indexHead;
	SkipList(int _maxLevel): maxLevel(_maxLevel), indexHead(new IndexNode){}


};

#endif // !__LIST2
