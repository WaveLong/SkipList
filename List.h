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
    //打印
    void printList();
    //增
    void addValueForKey(const K& key, const V& value);
    //查
    DataNode<V>* getValueForKey(const K& key);
    //删
    void removeValueForKey(const K& key);
    //改
    void setValueForKey(const K& key, const V& value);
    //查找节点
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
        std::cout << "key已经存在！" << std::endl;
        return;
    }
    // 构造节点
    DataNode<V>* tmpDataNode = new DataNode<V>(value);
    IndexNode<K, V>* newIndexNode = new IndexNode<K, V>(key, tmpDataNode), * prev;
    // 插入位置
    IndexNode<K, V>* cur = searchPath.top();
    searchPath.pop();
    // 插入KV对
    newIndexNode->right = cur->right;
    cur->right = newIndexNode;
    prev = newIndexNode;

    while (!searchPath.empty()) {
        //以一定的概率决定是否需要增加索引
        double p = rand() / double(RAND_MAX);
        if (p > listProb) break;
        // 增加索引
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
    if (!flag) std::cout << "key不存在" << std::endl;
}

template <typename K, typename V>
void SkipList<K, V>::setValueForKey(const K& key, const V& value) {
    IndexNode<K, V>* node = searchIndexNodeForKey(key);
    if (!node || node->key != key) {
        std::cout << "key不存在，插入新的值" << std::endl;
        addValueForKey(key, value);
    }
    else {
        std::cout << "key已经存在，修改为新的值" << std::endl;
        node->data->value = value;
    }
}

//假设key是合法的
template <typename K, typename V>
IndexNode<K, V>* SkipList<K, V>::searchIndexNodeForKey(const K& key) {
    //确保searchPath是空的
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