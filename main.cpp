#include <iostream>
#include "src-v1/List.h"
#include "src-v1/Node.h"
using namespace std;

int main() {
    //≥ı ºªØ
    SkipList<int, int> l = SkipList<int, int>(5);
    l.printList();
    // ≤Â»Î
    for (int i = 0; i < 20; ++i) {
        l.addValueForKey(i, i+1);
    }
    l.printList();
    // ≤Â»Î≥ÂÕª
    l.addValueForKey(1, -1);
    l.printList();

    //÷ÿ÷√
    l.setValueForKey(1, -5);
    l.printList();

    //“∆≥˝
    l.removeValueForKey(3);
    l.printList();
    l.removeValueForKey(5);
    l.printList();
    l.removeValueForKey(7);
    l.printList();

    return 0;
}
