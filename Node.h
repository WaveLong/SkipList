#ifndef __NODE
#define __NODE
//用于存储重复key的
template <class V>
class DataNode {
public:
    V value; // 数据
    DataNode<V>* next; // 下一个节点
    DataNode(const V& _value, DataNode<V>* _next = nullptr) : value(_value), next(_next) {}
};

// 索引节点
template <class K, class V>
class IndexNode {
public:
    K key;
    DataNode<V>* data; // 指向数据，对于h0层以外的节点，该指针为空
    IndexNode<K, V>* down, * right; // 指向索引节点
    IndexNode(const K& _key, DataNode<V>* _data = nullptr) {
        down = right = nullptr;
        key = _key;
        data = _data;
    }
};
#endif // !__NODE