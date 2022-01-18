//
// Created by Jan Halemba on 08/01/2022.
//

#ifndef TREE_DICTIONARY_H
#define TREE_DICTIONARY_H

template <typename Key, typename Info>
class Dictionary {
private:
    friend class Node;
    class Node {
        friend class Dictionary;
    public:
        Node(Key key, Info info) : key_(key), info_(info), balance_factor(0), left_(nullptr), right_(right_) {};
        Key getKey() { return key_; };
        Info getInfo() { return info_; };
        int getBalanceFactor() { return balance_factor; };
    private:
        Key key_;
        Info info_;
        int balance_factor;
        Node* left_;
        Node* right_;
        void setLeft(Node* left) { left_ = left; };
        void setRight(Node* right) { right_ = right; };
        Node*& getLeft() { return left_; };
        Node*& getRight() { return right_; };
    };
    void rotateLeft(Node*& root);
    void rotateRight(Node*& root);
    void insertAVL(Node*& root, Node* newNode, bool& isTaller);
    void balanceFromLeft(Node*& root);
    void balanceFromRight(Node*& root);
    void deleteNode(Node*& p);
public:
    Dictionary() : root(nullptr) {};
    ~Dictionary();
    bool search(const Key& key) const;
    void insert(const Key& key, const Info& info);
protected:
    Node* root;
};

template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary() {
    deleteNode(root);
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::search(const Key &key) const {
    auto* current = root;
    bool found = false;

    if (root == nullptr)
        std::cerr << "Cannot search as the tree is empty!" << std::endl;
    else
    {
        while (current != nullptr && !found)
        {
            if (current->getInfo() == key)
                found = true;
            else if (current->getInfo() > key)
                current = current->getLeft();
            else
                current = current->getRight();
        }
    }
    return found;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::rotateLeft(Dictionary::Node *&root) {
    if (root == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "The tree is empty!" << std::endl;
    else if (root->getRight() == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "Nothing to rotate!" << std::endl;
    else
    {
        auto* p = root->getRight();
        root->setRight(p->getLeft());

        p->setLeft(root);
        root = p;
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::rotateRight(Dictionary::Node *&root) {
    if (root == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "The tree is empty!" << std::endl;
    else if (root->getLeft() == nullptr)
        std::cerr << "Unable to rotate." << std::endl
                  << "Nothing to rotate!" << std::endl;
    else
    {
        auto* p = root->getLeft();
        root->setLeft(p->getRight());

        p->setRight(root);
        root = p;
    }
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::balanceFromLeft(Node*& root) {
    Node *p;
    Node *w;
    p = root->getLeft();
    switch (p->balance_factor)
    {
//p points to the left subtree of root
        case -1:
            root->balance_factor = 0;
            p->balance_factor = 0;
            rotateRight(root);
            break;
        case 0:
            std::cerr << "Error: Cannot balance from the left." << std::endl;
            break;
        case 1:
            w = p->getRight();
            switch (w->balance_factor)
            {
//adjust the balance factors
                case -1:
                    root->balance_factor = 1;
                    p->balance_factor = 0;
                    break;
                case 0:
                    root->balance_factor = 0;
                    p->balance_factor = 0;
                    break;
                case 1:
                    root->balance_factor = 0;
                    p->balance_factor = -1;
            }//end switch
            w->balance_factor = 0;
            rotateLeft(p);
            root->setLeft(p);
            rotateRight(root);
    }//end switch;
}//end balanceFromLeft

template <typename Key, typename Info>
void Dictionary<Key, Info>::balanceFromRight(Node*& root) {
    Node *p;
    Node *w;
    p = root->getRight();
    switch (p->balance_factor)
    {
        case -1:
            w = p->getLeft();
            switch (w->balance_factor)
            {
                case -1:
                    root->balance_factor = 0;
                    p->balance_factor = 1;
                    break;
                case 0:
                    root->balance_factor = 0;
                    p->balance_factor = 0;
                    break;
                case 1:
                    root->balance_factor = -1;
                    p->balance_factor = 0;
            }//end switch
            w->balance_factor = 0;
            rotateRight(p);
            root->setRight(p);
            rotateLeft(root);
            break;
        case 0:
            std::cerr << "Error: Cannot balance from the left." << std::endl;
            break;
        case 1:
            root->balance_factor = 0;
            p->balance_factor = 0;
            rotateLeft(root);
    }//end switch;
}//end balanceFromRight

template<typename Key, typename Info>
void Dictionary<Key, Info>::insertAVL(Dictionary::Node *&root, Dictionary::Node *newNode, bool &isTaller) {
    if (root == nullptr)
    {
        root = newNode;
        isTaller = true;
    }
    else if (root->getKey() == newNode->getKey())
        std::cerr << "No duplicates are allowed." << std::endl;
    else if (root->getKey() > newNode->getKey())
    {
        insertAVL(root->getLeft(), newNode, isTaller);
        if (isTaller)
            switch (root->balance_factor) {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->balance_factor = -1;
                isTaller = true;
                break;
            case 1:
                root->balance_factor = 0;
                isTaller = false;
                break;
            }
    }
    else
    {
        insertAVL(root->getRight(), newNode, isTaller);

        if (isTaller)
            switch (root->balance_factor) {
            case -1:
                root->balance_factor = 0;
                isTaller = false;
                break;
            case 0:
                root ->balance_factor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
            }
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key &key, const Info &info) {
    bool isTaller = false;
    auto* newNode = new Node(key, info);
    newNode ->balance_factor = 0;

    insertAVL(root, newNode, isTaller);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::deleteNode(Dictionary::Node *&p) {
    if (p != nullptr)
    {
        deleteNode(p->getLeft());
        deleteNode(p->getRight());
        delete p;
        p = nullptr;
    }
}

#endif //TREE_DICTIONARY_H
