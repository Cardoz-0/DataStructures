// Copyright [2021] FOSS
#include "array_list.h"

namespace structures {
template<typename T>
class BinaryTree {
    struct Node;
    public:
        BinaryTree() {
            root = nullptr;
            size_ = 0;
        }

        ~BinaryTree() = default;

        void insert(const T& data) {
            if (root == nullptr) {
                root = new Node(data);
            } else if (data > root->data()) {
                if (root->right() == nullptr) {
                    root->right(new Node(data));
                } else {
                    root->right()->insert(data);
                }
            } else {
                if (root->left() == nullptr) {
                    root->left(new Node(data));
                } else {
                    root->left()->insert(data);
                }
            }
            size_++;
        }

        void remove(const T& data) {
            if (contains(data)) {
            root->remove(data, root);
            size_--;
            }
        }

        T menor_root() {
            return (root->min_node(root))->data();
        }

        bool contains(const T& data) const {
            if (size_ == 0)
                return false;
            return root->contains(data);
        }

        bool empty() const {
            if (size_ == 0) {
                return true;
            } else {
                return false;
            }
        }

        std::size_t size() const {
            return size_;
        }

        ArrayList<T> pre_order() const {
            ArrayList<T> list{size_};
            root->pre_order(list);
            return list;
        }

        ArrayList<T> in_order() const {
            ArrayList<T> list{size_};
            root->in_order(list);
            return list;
        }

        ArrayList<T> post_order() const {
            ArrayList<T> list{size_};
            root->post_order(list);
            return list;
        }

    private:
        struct Node {
            explicit Node(const T& data_) {
                _data = data_;
                _left = nullptr;
                _right = nullptr;
            }

            T _data;
            Node* _left;
            Node* _right;
            T data() {
                return _data;
            }

            Node* left() {
                return _left;
            }

            Node* right() {
                return _right;
            }

            void data(T data) {
                _data = data;
            }

            void left(Node* left) {
                _left = left;
            }

            void right(Node* right) {
                _right = right;
            }

            Node* min_node(Node* self) {
                auto current_node = self;
                    while (current_node->left())
                        current_node = current_node->left();
                return current_node;
            }

            void insert(const T& data_) {
                if (data_ > _data) {
                    if (_right == nullptr) {
                        _right = new Node(data_);
                    } else {
                        _right->insert(data_);
                    }

                } else {
                    if (_left == nullptr) {
                        _left = new Node(data_);
                    } else {
                        _left->insert(data_);
                    }
                }
            }

            bool remove(const T& data_, Node* parent) {
                if (data_ > _data) {
                    if (_right == nullptr) {
                        return false;
                    } else {
                        _right->remove(data_, this);
                    }

                } else if (data_ < _data) {
                    if (_left == nullptr) {
                        return false;
                    } else {
                        _left->remove(data_, this);
                    }

                } else {
                    if (is_leaf()) {
                        delete this;
                        return true;

                    } else if (    (_right != nullptr && _left == nullptr)
                                || (_right == nullptr && _left != nullptr)) {
                        if (this == parent->left()) {
                            if (_left != nullptr) {
                                parent->left(_left);
                                delete this;
                                return true;
                            }
                            if (_right != nullptr) {
                                parent->left(_right);
                                delete this;
                                return true;
                            }
                        }

                        if (this == parent->right()) {
                            if (_left != nullptr) {
                                parent->right(_left);
                                delete this;
                                return true;
                            }
                            if (_right != nullptr) {
                                parent->right(_right);
                                delete this;
                                return true;
                            }
                        }
                    } else {
                        if (_right->left() == nullptr) {
                            _data = _right->data();
                            auto temp_right = _right;
                            delete _right;
                            _right = temp_right;
                            return true;
                        } else {
                            auto lefty = _right->min_node(_right);
                            _data = lefty->data();
                            delete lefty;
                        }
                    }
                }
                return false;
            }

            bool contains(const T& data_) const {
                if (data_ == _data) {
                    return true;
                } else if (data_ > _data) {
                    if (_right == nullptr) {
                        return false;
                    } else {
                        return _right->contains(data_);
                    }
                } else {
                    if (_left == nullptr) {
                        return false;
                    } else {
                        return _left->contains(data_);
                    }
                }
            }

            bool is_leaf() {
                return (_right == nullptr && _left == nullptr);
            }

            void pre_order(ArrayList<T>& v) const {
                v.push_back(_data);
                if (_left != nullptr)
                    _left->pre_order(v);
                if (_right != nullptr)
                    _right->pre_order(v);
            }

            void in_order(ArrayList<T>& v) const {
                if (_left != nullptr)
                    _left->in_order(v);
                v.push_back(_data);
                if (_right != nullptr)
                    _right->in_order(v);
            }

            void post_order(ArrayList<T>& v) const {
                if (_left != nullptr)
                    _left->post_order(v);
                if (_right != nullptr)
                    _right->post_order(v);
                v.push_back(_data);
            }
        };

        Node* root;
        std::size_t size_;
        structures::ArrayList<T> list_ {};
};
}  // namespace structures
