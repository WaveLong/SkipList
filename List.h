#ifndef __LIST
#define __LIST

#include <iostream>
#include <stack>
#include <cstdlib>
#include <time.h>
#include "Node.h"

template <typename K, typename V>
class SkipList {
private:
    std::stack<IndexNode<K, V>*> searchPath;
    double listProb;
    int maxLevel;
public:
    IndexNode<K, V>** indexHead;
    SkipList(int _maxLevel = 16) : maxLevel(_maxLevel) {
        srand((unsigned)time(NULL));
        listProb = 0.5;
        keyCount = 0;

        indexHead = new IndexNode<K, V> * [_maxLevel];
        for (int i = 0; i < _maxLevel; ++i) {
            indexHead[i] = new IndexNode<K, V>(-1);
            if (i > 0) indexHead[i]->down = indexHead[i - 1];
        }
    }
    ~SkipList() {
        for (int i = 0; i < maxLevel; ++i)delete indexHead[i];
        delete[]indexHead;
    }
    //��ӡ
    void printList();
    //��
    void addValueForKey(const K& key, const V& value);
    //��
    DataNode<V>* getValueForKey(const K& key);
    //ɾ
    void removeValueForKey(const K& key);
    //��
    void setValueForKey(const K& key, const V& value);
    //���ҽڵ�
    IndexNode<K, V>* searchIndexNodeForKey(const K& key);
};

template <typename K, typename V>
void SkipList<K, V>::printList() {
    IndexNode<K, V>* cur;
    for (int i = maxLevel - 1; i >= 0; --i) {
        std::cout << "level = " << i << std::endl;
        cur = indexHead[i]->right;
        while (cur) {
            std::cout << cur->key << "\t";
            cur = cur->right;
        }
        std::cout << std::endl;
    }
    cur = indexHead[0]->right;
    while (cur) {
        std::cout << cur->data->value << "\t";
        cur = cur->right;
    }
    std::cout << std::endl;
}

template <typename K, typename V>
void SkipList<K, V>::addValueForKey(const K& key, const V& value) {
    IndexNode<K, V>* node = searchIndexNodeForKey(key);
    if (node && node->key == key) {
        std::cout << "key�Ѿ����ڣ�" << std::endl;
        return;
    }
    // ����ڵ�
    DataNode<V>* tmpDataNode = new DataNode<V>(value);
    IndexNode<K, V>* newIndexNode = new IndexNode<K, V>(key, tmpDataNode), * prev;
    // ����λ��
    IndexNode<K, V>* cur = searchPath.top();
    searchPath.pop();
    // ����KV��
    newIndexNode->right = cur->right;
    cur->right = newIndexNode;
    prev = newIndexNode;

    while (!searchPath.empty()) {
        //��һ���ĸ��ʾ����Ƿ���Ҫ��������
        double p = rand() / double(RAND_MAX);
        if (p > listProb) break;
        // ��������
        cur = searchPath.top();
        searchPath.pop();

        newIndexNode = new IndexNode<K, V>(key);
        newIndexNode->right = cur->right;
        cur->right = newIndexNode;
        newIndexNode->down = prev;

        prev = newIndexNode;
    }
}

template <typename K, typename V>
DataNode<V>* SkipList<K, V>::getValueForKey(const K& key) {
    IndexNode<K, V>* node = searchIndexNodeForKey(key);
    return (node->key == key) ? node->data : nullptr;
}

template <typename K, typename V>
void SkipList<K, V>::removeValueForKey(const K& key) {
    IndexNode<K, V>* cur = indexHead[maxLevel - 1], * tmp;
    bool flag = false;
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (cur->right && cur->right->key < key)cur = cur->right;
        tmp = cur->right;
        if (tmp && tmp->key == key) {
            cur->right = tmp->right;
            delete tmp;
            flag = true;
        }
        cur = cur->down;
    }
    if (!flag) std::cout << "key������" << std::endl;
}

template <typename K, typename V>
void SkipList<K, V>::setValueForKey(const K& key, const V& value) {
    IndexNode<K, V>* node = searchIndexNodeForKey(key);
    if (!node || node->key != key) {
        std::cout << "key�����ڣ������µ�ֵ" << std::endl;
        addValueForKey(key, value);
    }
    else {
        std::cout << "key�Ѿ����ڣ��޸�Ϊ�µ�ֵ" << std::endl;
        node->data->value = value;
    }
}

//����key�ǺϷ���
template <typename K, typename V>
IndexNode<K, V>* SkipList<K, V>::searchIndexNodeForKey(const K& key) {
    //ȷ��searchPath�ǿյ�
    while (!searchPath.empty())searchPath.pop();
    IndexNode<K, V>* cur = indexHead[maxLevel - 1];
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (cur->right != nullptr && cur->right->key <= key)cur = cur->right;
        searchPath.push(cur);
        if (i == 0) break;
        cur = cur->down;
    }
    return cur;
}

#endif