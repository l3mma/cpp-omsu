#include "BTree.h"
#include <iostream>

using namespace std;

int main() {
    BTree tree;
    
    tree.addElement(10, {});
    tree.addElement(5, {0});
    tree.addElement(15, {1});
    tree.addElement(3, {0, 0});
    tree.addElement(7, {0, 1});
    
    cout << "Tree: " << tree << endl;
    cout << "Even count: " << tree.getEvenCount() << endl;
    cout << "All positive: " << boolalpha << tree.isAllPositive() << endl;
    cout << "Average: " << tree.getAverage() << endl;
    cout << "Is BST: " << tree.isBST() << endl;
    
    auto path = tree.find(7);
    cout << "Path to 7: ";
    for (int p : path) cout << p << " ";
    cout << endl;
    
    tree.deleteLeaves();
    cout << "After delete leaves: " << tree << endl;
    
    return 0;
}