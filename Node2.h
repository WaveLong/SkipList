#ifndef __NODE2
#define __NODE2

template<class V>
class DataNode {
public:
	V value;
	DataNode<V>* next;
	DataNode(V _value) : value(_value), next(nullptr) {}
};

template<class K, class V>
class IndexNode {
public:
	int height;
	IndexNode<K, V>** nexts;
	K key;
	DataNode<V>* data;

	IndexNode(K _key, int _h) {
		key = _key;
		height = _h;
		data = nullptr;
		nexts = new IndexNode<K, V> * [_h];
		for (int i = 0; i < _h; ++i)nexts[i] = nullptr;
	}
	~IndexNode() {
		delete[] nexts;
	}
};


#endif // !__NODE2

