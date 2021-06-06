#include <iostream>
#include "src-v1/List.h"
#include "src-v1/Node.h"
using namespace std;

int main() {
    //��ʼ��
    SkipList<int, int> l = SkipList<int, int>(5);
    l.printList();
    // ����
    for (int i = 0; i < 20; ++i) {
        l.addValueForKey(i, i+1);
    }
    l.printList();
    // �����ͻ
    l.addValueForKey(1, -1);
    l.printList();

    //����
    l.setValueForKey(1, -5);
    l.printList();

    //�Ƴ�
    l.removeValueForKey(3);
    l.printList();
    l.removeValueForKey(5);
    l.printList();
    l.removeValueForKey(7);
    l.printList();

    return 0;
}
