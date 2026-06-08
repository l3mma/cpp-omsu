#pragma once
#include <iostream>
#include <string>

class BSTree {
private:
    struct Node {
        std::string word;
        int count;
        Node* left;
        Node* right;
        Node(const std::string& w) : word(w), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clearTree(Node* node);
    Node* copyTree(Node* node);
    Node* insertNode(Node* node, const std::string& word);
    Node* removeNode(Node* node, const std::string& word);
    Node* findMin(Node* node);
    Node* findNode(Node* node, const std::string& word) const;
    int getTotalWords(Node* node) const;
    void printTree(Node* node, std::ostream& os) const;

public:
    BSTree();
    BSTree(const BSTree& other);
    ~BSTree();
    BSTree& operator=(const BSTree& other);

    int find(const std::string& word) const;
    void insert(const std::string& word);
    void remove(const std::string& word);
    int totalWords() const;
    bool empty() const;

    friend std::ostream& operator<<(std::ostream& os, const BSTree& tree);
};