#ifndef __NODE
#define __NODE
//���ڴ洢�ظ�key��
template <class V>
class DataNode {
public:
    V value; // ����
    DataNode<V>* next; // ��һ���ڵ�
    DataNode(const V& _value, DataNode<V>* _next = nullptr) : value(_value), next(_next) {}
};

// �����ڵ�
template <class K, class V>
class IndexNode {
public:
    K key;
    DataNode<V>* data; // ָ�����ݣ�����h0������Ľڵ㣬��ָ��Ϊ��
    IndexNode<K, V>* down, * right; // ָ�������ڵ�
    IndexNode(const K& _key, DataNode<V>* _data = nullptr) {
        down = right = nullptr;
        key = _key;
        data = _data;
    }
};
#endif // !__NODE