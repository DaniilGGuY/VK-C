#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "bst_iterator.h"
#include "binary_tree.h" 

template<class Key, class T, class Compare, class Allocator, bool IsConst>
typename bst_iterator<Key, T, Compare, Allocator, IsConst>::reference
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator*() const {
    return current_->data;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
typename bst_iterator<Key, T, Compare, Allocator, IsConst>::pointer
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator->() const {
    return &current_->data;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
typename bst_iterator<Key, T, Compare, Allocator, IsConst>::node_ptr
bst_iterator<Key, T, Compare, Allocator, IsConst>::findMin(node_ptr node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
typename bst_iterator<Key, T, Compare, Allocator, IsConst>::node_ptr
bst_iterator<Key, T, Compare, Allocator, IsConst>::findMax(node_ptr node) const {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
bst_iterator<Key, T, Compare, Allocator, IsConst>& 
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator++() {
    if (!current_) return *this;
    
    if (current_->right) {
        current_ = findMin(current_->right);
    } else {
        node_ptr parent = current_->parent;
        while (parent && current_ == parent->right) {
            current_ = parent;
            parent = parent->parent;
        }
        current_ = parent;
    }
    return *this;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
bst_iterator<Key, T, Compare, Allocator, IsConst> 
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
bst_iterator<Key, T, Compare, Allocator, IsConst>& 
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator--() {
    if (!current_) {
        return *this;
    }
    
    if (current_->left) {
        current_ = findMax(current_->left);
    } else {
        node_ptr parent = current_->parent;
        while (parent && current_ == parent->left) {
            current_ = parent;
            parent = parent->parent;
        }
        current_ = parent;
    }
    return *this;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
bst_iterator<Key, T, Compare, Allocator, IsConst> 
bst_iterator<Key, T, Compare, Allocator, IsConst>::operator--(int) {
    auto temp = *this;
    --(*this);
    return temp;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
template<bool OtherConst>
bool bst_iterator<Key, T, Compare, Allocator, IsConst>::operator==(
    const bst_iterator<Key, T, Compare, Allocator, OtherConst>& other) const {
    return current_ == other.current_;
}

template<class Key, class T, class Compare, class Allocator, bool IsConst>
template<bool OtherConst>
bool bst_iterator<Key, T, Compare, Allocator, IsConst>::operator!=(
    const bst_iterator<Key, T, Compare, Allocator, OtherConst>& other) const {
    return !(*this == other);
}

#endif