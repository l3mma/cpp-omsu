#include "BTree.h"

Node::Node(int data, Node* left, Node* right)
    : data_(data), left_(left), right_(right) {}

Node* BTree::copy(const Node* node) {
    if (!node) return nullptr;
    return new Node(node->data_, copy(node->left_), copy(node->right_));
}

int BTree::getEvenCount(const Node* node) const {
    if (!node) return 0;
    // проверка четности + проход по левой, правой части дерева
    int count = (node->data_ % 2 == 0) ? 1 : 0;
    return count + getEvenCount(node->left_) + getEvenCount(node->right_);
}

bool BTree::allPositive(const Node* node) const {
    if (!node) return true;
    return node->data_ > 0 && allPositive(node->left_) && allPositive(node->right_);
}

void BTree::clear(Node* node) {
    if (!node) return;
    clear(node->left_);
    clear(node->right_);
    delete node;
}

void BTree::deleteLeaves(Node* node, Node* parent, bool isLeft) {
    if (!node) return;
    
    // лист, нету потомка
    if (!node->left_ && !node->right_) {
        if (parent) {
            if (isLeft) parent->left_ = nullptr;
            else parent->right_ = nullptr;
        }
        delete node;
    } else {
        deleteLeaves(node->left_, node, true);
        deleteLeaves(node->right_, node, false);
    }
}

double BTree::sum(const Node* node, int& count) const {
    if (!node) return 0;
    //count для среднего
    count++;
    return node->data_ + sum(node->left_, count) + sum(node->right_, count);
}

bool BTree::find(const Node* node, int x, std::vector<int>& path) const {
    if (!node) return false;
    if (node->data_ == x) return true;
    
    path.push_back(0);
    if (find(node->left_, x, path)) return true;
    path.pop_back();
    
    path.push_back(1);
    if (find(node->right_, x, path)) return true;
    path.pop_back();
    
    return false;
}

bool BTree::isBST(const Node* node, int min, int max) const {
    if (!node) return true;
    if (node->data_ <= min || node->data_ >= max) return false;
    return isBST(node->left_, min, node->data_) && 
           isBST(node->right_, node->data_, max);
}

BTree::BTree() : root_(nullptr) {}

BTree::BTree(const BTree& other) : root_(copy(other.root_)) {}

BTree& BTree::operator=(const BTree& other) {
    if (this != &other) {
        clear(root_);
        root_ = copy(other.root_);
    }
    return *this;
}

BTree::BTree(BTree&& other) noexcept : root_(other.root_) {
    other.root_ = nullptr;
}

BTree& BTree::operator=(BTree&& other) noexcept {
    if (this != &other) {
        clear(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

BTree::~BTree() {
    clear(root_);
}

bool BTree::addElement(int x, const std::vector<int>& path) {
    for (int dir : path) {
        if (dir != 0 && dir != 1) return false;
    }
    
    if (path.empty()) {
        if (!root_) root_ = new Node(x);
        else root_->data_ = x;
        return true;
    }
    
    Node* current = root_;
    if (!current) return false;
    
    // проход по пути
    for (int i = 0; i < path.size() - 1; ++i) {
        if (path[i] == 0) {
            if (!current->left_) return false;
            current = current->left_;
        } else {
            if (!current->right_) return false;
            current = current->right_;
        }
    }
    
    // вставка/замена элемента
    int lastDir = path.back();
    if (lastDir == 0) {
        if (!current->left_) current->left_ = new Node(x);
        else current->left_->data_ = x;
    } else {
        if (!current->right_) current->right_ = new Node(x);
        else current->right_->data_ = x;
    }
    return true;
}

int BTree::getEvenCount() const {
    return getEvenCount(root_);
}

bool BTree::isAllPositive() const {
    return allPositive(root_);
}

void BTree::deleteLeaves() {
    if (!root_) return;
    if (!root_->left_ && !root_->right_) {
        delete root_;
        root_ = nullptr;
        return;
    }
    deleteLeaves(root_->left_, root_, true);
    deleteLeaves(root_->right_, root_, false);
}

double BTree::getAverage() const {
    int count = 0;
    double _sum = sum(root_, count);
    return count > 0 ? _sum / count : 0.0;
}

std::vector<int> BTree::find(int x) const {
    std::vector<int> path;
    if (find(root_, x, path)) return path;
    return {-1};
}

bool BTree::isEmpty() const {
    return root_ == nullptr;
}

bool BTree::isBST() const {
    return isBST(root_, INT_MIN, INT_MAX);
}

//распечатка дерева
static void printInOrder(std::ostream& os, Node* node) {
    if (!node) return;
    printInOrder(os, node->left_);
    os << node->data_ << " ";
    printInOrder(os, node->right_);
}

std::ostream& operator<<(std::ostream& os, const BTree& tree) {
    if (!tree.root_) {
        os << "Tree is empty";
        return os;
    }
    printInOrder(os, tree.root_);
    return os;
}