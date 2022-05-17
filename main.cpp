#include <bits/stdc++.h>
#include "redblack.h"
using namespace std;

int main()
{
    RBTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    tree.inorder();
    tree.levelOrder();

    tree.Delete(18);
    tree.Delete(11);
    tree.Delete(3);
    tree.Delete(10);
    tree.Delete(22);

    tree.inorder();
    tree.levelOrder();
    cout<<tree.search(22)<<' '<<tree.search(21);
    return 0;
}
