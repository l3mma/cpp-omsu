#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data_;
    Node* left_;
    Node* right_;
    
    Node(int data = 0, Node* left = nullptr, Node* right = nullptr);
};

class BTree {
private:
    Node* root_;
    
    void clear(Node* node);
    Node* copy(const Node* node);
    int getEvenCount(const Node* node) const;
    bool allPositive(const Node* node) const;
    void deleteLeaves(Node* node, Node* parent, bool isLeft);
    double sum(const Node* node, int& count) const;
    bool find(const Node* node, int x, std::vector<int>& path) const;
    bool isBST(const Node* node, int min, int max) const;
    
public:
    BTree();
    BTree(const BTree& other);
    BTree& operator=(const BTree& other);
    BTree(BTree&& other) noexcept;
    BTree& operator=(BTree&& other) noexcept;
    ~BTree();
    
    bool addElement(int x, const std::vector<int>& path);
    int getEvenCount() const;
    bool isAllPositive() const;
    void deleteLeaves();
    double getAverage() const;
    std::vector<int> find(int x) const;
    bool isEmpty() const;
    bool isBST() const;
    
    friend std::ostream& operator<<(std::ostream& os, const BTree& tree);
};

#endif