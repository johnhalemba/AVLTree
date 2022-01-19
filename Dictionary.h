//
// Created by Jan Halemba on 08/01/2022.
//

#ifndef TREE_DICTIONARY_H
#define TREE_DICTIONARY_H
#include <iostream>
#include <sstream>

int max(int a, int b) {
    return (a > b) ? a : b;
}

class Node;

template <typename Key, typename Info>
class Dictionary {
private:
    friend class Node;
    class Node {
        friend class Dictionary;
    public:
        Node(Key key, Info info) : key_(key), info_(info), balance_factor(0), parent_(nullptr), left_(nullptr), right_(nullptr), height_(0) {};
        Key getKey() { return key_; };
        Info getInfo() { return info_; };
        int getHeight() { return height_; };
        int getBalanceFactor() { return balance_factor; };
        void addInfo() { info_++; };
        Node*& getLeft() { return left_; };
        Node*& getRight() { return right_; };
        Node*& getParent()  { return parent_; };
    private:
        Key key_;
        Info info_;
        int balance_factor;
        int height_;
        Node* left_;
        Node* right_;
        Node* parent_;
        void setLeft(Node* left) { left_ = left; };
        void setRight(Node* right) { right_ = right; };
    };
    void rotateLeft(Node*& root);
    void rotateRight(Node*& root);
    void insertRec(Node*& root, Node*& newNode, bool& duplicate);
    void clear(Node*& p);
    Node* findMinimum (Node*& root);
    Node* findMaximum (Node*& root);
    void balance(Node*& root);
    int diff(Node* temp);
    std::string recursiveCallback(Node* node);
    int height(Node* temp);
    void deleteNode(Node*& root);
    int getDiff() { return diff(root_); };
    int getHeight() { return height(root_); };
    void printInOrder(Node* root);

public:
    Dictionary() : root_(nullptr) {};
    ~Dictionary();
    bool search(const Key& key) const;
    void insert(const Key& key, const Info& info);
    Node* get(const Key& key);
    void remove(const Key& key);
    Node* getRoot() { return root_; };
    void printAscending() { printInOrder(root_); };
    void printPrittier() { std::cout << recursiveCallback(root_); };

protected:
    Node* root_;
};

template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary() {
    clear(root_);
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::search(const Key &key) const {
    auto* current = root_;
    bool found = false;

    if (root_ == nullptr)
        std::cerr << "Cannot search as the tree is empty!" << std::endl;
    else
    {
        while (current != nullptr && !found)
        {
            if (current->key_ == key)
                found = true;
            else if (current->key_ > key)
                current = current->left_;
            else
                current = current->right_;
        }
    }
    return found;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::rotateLeft(Dictionary::Node *&root) {
    if (root == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "The tree is empty!" << std::endl;
    else if (root->right_ == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "Nothing to rotate!" << std::endl;
    else
    {
        auto* p = root->right_;
        root->right_ = p->left_;
        p->left_ = root;
        root = p;
        if (root->left_ != nullptr)
        {
            root->left_->height_ = height(root->left_);
            root->left_->parent_ = root;
            if (root == root_)
                root_->parent_ = nullptr;
        }
        if (root->right_ != nullptr)
        {
            root->right_->height_ = height(root->right_);
            root->right_->parent_ = root;
            if (root == root_)
                root_->parent_ = nullptr;
        }
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::rotateRight(Dictionary::Node *&root) {
    if (root == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "The tree is empty!" << std::endl;
    else if (root->left_ == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "Nothing to rotate!" << std::endl;
    else
    {
        auto* p = root->left_;
        root->left_ = p->right_;
        p->right_ = root;
        root->height_ = height(root->right_);
        root = p;
        if (root->left_ != nullptr)
        {
            root->left_->height_ = height(root->left_);
            root->left_->balance_factor = diff(root->left_);
            root->left_->parent_ = root;
            if (root == root_)
                root_->parent_ = nullptr;
        }
        if (root->right_ != nullptr)
        {
            root->right_->height_ = height(root->right_);
            root->right_->balance_factor = diff(root->right_);
            root->right_->parent_ = root;
            if (root == root_)
                root_->parent_ = nullptr;
        }
    }
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::insertRec(Dictionary::Node *&root, Dictionary::Node *&newNode, bool& duplicate) {
    if (root == nullptr)
    {
        root = newNode;
    }
    else if (root->key_ == newNode->key_)
    {
        std::cerr << "No duplicates are allowed." << std::endl;
        duplicate = true;
    }
    else if (root->key_ > newNode->key_)
    {
        insertRec(root->left_, newNode, duplicate);
        balance(root);
    }
    else
    {
        insertRec(root->right_, newNode, duplicate);
        balance(root);
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key &key, const Info &info) {
    auto* newNode = new Node(key, info);
    newNode->balance_factor = 0;
    newNode->height_ = 0;
    bool isDuplicate = false;
    insertRec(root_, newNode, isDuplicate);
    if (isDuplicate)
        delete newNode;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::clear(Dictionary::Node *&p) {
    if (p != nullptr)
    {
        clear(p->getLeft());
        clear(p->getRight());
        delete p;
        p = nullptr;
    }
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::get(const Key &key) {
    auto* current = root_;
    bool found = false;

    if (root_ == nullptr)
        std::cerr << "Cannot search as the tree is empty!" << std::endl;
    else
    {
        while (current != nullptr && !found)
        {
            if (current->key_ == key)
                found = true;
            else if (current->key_ > key)
                current = current->left_;
            else
                current = current->right_;
        }
    }
    return current;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::findMinimum(Dictionary::Node *&root) {
    if (root == nullptr)
        return nullptr;
    else if (root->left_ == nullptr)
        return root;
    else
        return findMinimum(root->left_);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::findMaximum(Dictionary::Node *&root) {
    if (root == nullptr)
        return nullptr;
    else if (root->right_ == nullptr)
        return root;
    else
        return findMaximum(root->right_);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::height(Dictionary::Node *temp) {
    int h = 0;
    if (temp == nullptr)
        return -1;
    else
    {
        int l_height = height(temp->left_);
        int r_height = height(temp->right_);
        int max_height = std::max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::diff(Dictionary::Node *temp) {
    int l_height = height(temp->left_);
    int r_height = height(temp->right_);
    int b_factor = l_height - r_height;
    return b_factor;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::balance(Dictionary::Node *&root) {
    if (root->left_ != nullptr)
        root->left_ ->parent_ = root;
    if (root->right_ != nullptr)
        root->right_->parent_ = root;
    root->height_ = height(root);
    root->balance_factor = diff(root);
    if (root->balance_factor > 1) {
        if (diff(root->left_) > 0)
            rotateRight(root);
        else
        {
            rotateLeft(root->left_);
            rotateRight(root);
        }
    }
    else if (root->balance_factor < -1) {
        if (diff(root->right_) > 0)
        {
            rotateRight(root->right_);
            rotateLeft(root);
        }
        else {
            rotateLeft(root);
        }
    }
    root->height_ = height(root);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::deleteNode(Node*& root) {
    Node* currentElement;
    Node* previousElement;
    Node* to_delete;

    if (root == nullptr)
        std::cerr << "You cannot delete empty node!" << std::endl;
    else if (root->left_ == nullptr && root->right_ == nullptr)
    {
        to_delete = root;
        root = nullptr;
        delete to_delete;
    }
    else if (root->left_ == nullptr)
    {
        to_delete = root;
        root = to_delete->right_;
        delete to_delete;
    }
    else if (root->right_ == nullptr)
    {
        to_delete = root;
        root = to_delete->left_;
        delete to_delete;
    }
    else
    {
        currentElement = root->left_;
        previousElement = nullptr;

        while (currentElement->right_ != nullptr)
        {
            previousElement = currentElement;
            currentElement = currentElement->right_;
        }

        root->info_ = currentElement->info_;
        root->key_ = currentElement->key_;

        if (previousElement == nullptr)
        {
            root->left_ = currentElement->left_;
        }
        else
            previousElement->right_ = currentElement->left_;
        delete currentElement;
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::remove(const Key &key) {
    Node* current;
    Node* parentCurrent;
    bool found = false;

    if (root_ == nullptr)
        std::cerr << "Empty tree!" << std::endl;
    else
    {
        current = root_;
        parentCurrent = root_;
        while (current != nullptr && !found)
        {
            if (current->key_ == key)
                found = true;
            else
            {
                parentCurrent = current;

                if (current->key_ > key)
                    current = current->left_;
                else
                    current = current->right_;
            }
        }

        if (current == nullptr)
            std::cerr << "Element not found" << std::endl;
        else
        {
            if (current == root_)
            {
                deleteNode(root_);
                balance(root_);
            }
            else if (parentCurrent->key_ > key)
            {
                deleteNode(parentCurrent->left_);
                balance(parentCurrent);
            }
            else
            {
                deleteNode(parentCurrent->right_);
                balance(parentCurrent);
            }
        }
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::printInOrder(Node *root) {
    if (root == nullptr)
        return;
    printInOrder(root->left_);
    std::cout << root->key_ << std::endl;
    printInOrder(root->right_);
}

template<typename Key, typename Info>
std::string Dictionary<Key, Info>::recursiveCallback(Node* node){
    if(!node) return "";
    std::stringstream str;
    str << '[' << node -> key_ << " " << node -> info_ << ']';
    if(node->left_) str << recursiveCallback(node->left_);
    if(node->right_) str << recursiveCallback(node->right_);
    return str.str();
}

#endif //TREE_DICTIONARY_H
