// Copyright [2021] FOSS


#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <algorithm>
#include "array_list.h"

namespace structures {
template <typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
        }

        T data;
        int height_{0};
        Node* left{nullptr};
        Node* right{nullptr};

        Node* insert(Node* node, const T &data_) {
            if (node == NULL) {
                Node* nodenode = new Node(data_);
                return nodenode;
            }
            if (data_ < node->data) {
                node->left = insert(node->left, data_);
            } else if (data_ > node->data) {
                node->right = insert(node->right, data_);
            } else {
                throw std::out_of_range("Out of range. ");
            }
            node->height_ = std::max(height(node->left),
                                        height(node->right)) + 1;
            int roda = rodar(node);
            if (roda > 1 && data_ < node->left->data) {
                return LLeft(node);
            }
            if (roda < -1 && data_ > node->right->data) {
                return RRight(node);
            }
            if (roda > 1 && data_ > node->left->data) {
                node->left = RRight(node->left);
            }
            if (roda < -1 && data_ < node->right->data) {
                node->right = LLeft(node->right);
            }
            return node;
        }

        Node* RRight(Node *nod2) {
            Node *nod = nod2->right;
            nod2->right = nod->left;
            nod->left = nod2;
            nod2->height_ = std::max(height(nod2->left),
                                    height(nod2->right)) + 1;
            nod->height_ = std::max(height(nod->left),
                                    height(nod->right)) + 1;
            return nod;
        }

        Node* LLeft(Node *nod2) {
            Node *nod = nod2->left;
            nod2->left = nod->right;
            nod->right = nod2;
            nod2->height_ = std::max(height(nod2->left),
                                    height(nod2->right)) + 1;
            nod->height_ = std::max(height(nod->left),
                                    height(nod->right)) + 1;
            return nod;
        }

        int rodar(Node *nod) {
            if (nod == NULL)
                return 0;
            return height(nod->left) -
                    height(nod->right);
        }

        Node* remove(const T &data_) {
            Node *nodenode = this;
            if (data_ < nodenode->data) {
                nodenode->left = nodenode->left->remove(data_);
            } else if (data > nodenode->data) {
                nodenode->right = nodenode->right->remove(data_);
            } else {
                if ((nodenode->left == NULL) ||
                    (nodenode->right == NULL)
                ) {
                    Node *temp = nodenode->left ?
                                nodenode->left : nodenode->right;
                    if (temp == NULL) {
                        temp = nodenode;
                        nodenode = NULL;
                    } else {
                        *nodenode = *temp;
                        delete temp;
                    }
                } else {
                    Node *temp = nodenode->right;
                    nodenode->data = temp->data;
                    nodenode->right = nodenode->right->remove(temp->data);
                }
            }

            if (nodenode == NULL) return nodenode;
            nodenode->height_ = std::max(height(nodenode->left),
                                height(nodenode->right)) + 1;
            int nodeb = rodar(nodenode);
            if (
                nodeb > 1 &&
                rodar(nodenode->left) >= 0
            ) {
                return LLeft(nodenode);
            }
            if (
                nodeb < -1 &&
                rodar(nodenode->right) <= 0
            ) {
                return RRight(nodenode);
            }
            if (
                nodeb > 1 &&
                rodar(nodenode->left) < 0
            ) {
                nodenode->left = RRight(nodenode->left);
            }
            if (
                nodeb < -1 &&
                rodar(nodenode->right) > 0
            ) {
                nodenode->right = LLeft(nodenode->right);
            }
            return nodenode;
        }

        bool contains(const T &data_) const {
            if (data_ < data) {
                return left != NULL ? left->contains(data_) : false;
            } else if (data_ > data) {
                return right != NULL ? right->contains(data_) : false;
            } else if (data_ == data) {
                return true;
            } else {
                throw std::out_of_range("Out of range. ");
            }
        }

        void free() {
            if (right != NULL) right->free();
            if (left != NULL) left->free();
            if (this != NULL) delete this;
        }

        void pre_order(ArrayList<T> &v) const {
            v.push_back(data);
            if (left != NULL) left->pre_order(v);
            if (right != NULL) right->pre_order(v);
        }

        void post_order(ArrayList<T> &v) const {
            if (left != NULL) left->post_order(v);
            if (right != NULL) right->post_order(v);
            v.push_back(data);
        }

        void in_order(ArrayList<T> &v) const {
            if (left != NULL) left->in_order(v);
            v.push_back(data);
            if (right != NULL) right->in_order(v);
        }

        int height(Node *nod) {
            if (nod == NULL)
                return 0;
            return nod->height_;
        }
    };
    Node* root{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures
#endif

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height(root);
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (root != NULL) {
        if (data < root->data) {
            return root->left != NULL ? root->left->contains(data) : false;
        } else if (data > root->data) {
            return root->right != NULL ? root->right->contains(data) : false;
        } else if (data == root->data) {
            return true;
        } else {
            throw std::out_of_range("Out of range. ");
        }
    } else {
        return false;
    }
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0 ? true : false;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Empty tree. ");
    } else {
        root = root->remove(data);
        size_--;
    }
}

template<typename T>
void structures::AVLTree<T>::insert(const T &data) {
    root = root->insert(root, data);
    size_++;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> lista;
    if (root != NULL) {
        root->post_order(lista);
    }
    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> lista;
    if (root != NULL) {
        root->in_order(lista);
    }
    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> list;
    if (root != NULL) {
        root->pre_order(list);
    }
    return list;
}
