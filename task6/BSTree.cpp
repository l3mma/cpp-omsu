#include "BSTree.h"

BSTree::BSTree() : root(nullptr) {}

BSTree::BSTree(const BSTree& other) : root(nullptr) {
    root = copyTree(other.root);
}

BSTree::~BSTree() {
    clearTree(root);
}

BSTree& BSTree::operator=(const BSTree& other) {
    if (this != &other) {
        clearTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

void BSTree::clearTree(Node* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

BSTree::Node* BSTree::copyTree(Node* node) {
    if (!node) return nullptr;
    Node* newNode = new Node(node->word);
    newNode->count = node->count;
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

//спуск по левой ветке
BSTree::Node* BSTree::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

BSTree::Node* BSTree::findNode(Node* node, const std::string& word) const {
    if (!node) return nullptr;
    if (word < node->word) return findNode(node->left, word);
    if (word > node->word) return findNode(node->right, word);
    return node;
}

int BSTree::find(const std::string& word) const {
    Node* node = findNode(root, word);
    return node ? node->count : 0;
}

BSTree::Node* BSTree::insertNode(Node* node, const std::string& word) {
    if (!node) return new Node(word);
    if (word < node->word) node->left = insertNode(node->left, word);
    else if (word > node->word) node->right = insertNode(node->right, word);
    else node->count++;
    return node;
}

void BSTree::insert(const std::string& word) {
    root = insertNode(root, word);
}

BSTree::Node* BSTree::removeNode(Node* node, const std::string& word) {
    if (!node) return nullptr;
    //ищем узел
    if (word < node->word) {
        node->left = removeNode(node->left, word);
    } else if (word > node->word) {
        node->right = removeNode(node->right, word);
    } else {
        if (node->count > 1) {
            node->count--;
            return node;
        }
        //подслучай - нет потомка
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        //два потомка
        Node* temp = findMin(node->right);
        node->word = temp->word;
        node->count = temp->count;
        node->right = removeNode(node->right, temp->word);
    }
    return node;
}

void BSTree::remove(const std::string& word) {
    root = removeNode(root, word);
}

int BSTree::getTotalWords(Node* node) const {
    if (!node) return 0;
    return node->count + getTotalWords(node->left) + getTotalWords(node->right);
}

int BSTree::totalWords() const {
    return getTotalWords(root);
}

bool BSTree::empty() const {
    return root == nullptr;
}

//вывод в алфавитном порядке
void BSTree::printTree(Node* node, std::ostream& os) const {
    if (!node) return;
    printTree(node->left, os);
    os << node->word << ": " << node->count << std::endl;
    printTree(node->right, os);
}

std::ostream& operator<<(std::ostream& os, const BSTree& tree) {
    tree.printTree(tree.root, os);
    return os;
}