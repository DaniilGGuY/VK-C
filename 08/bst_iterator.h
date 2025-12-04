#ifndef BST_ITERATOR_H
#define BST_ITERATOR_H

#include <iterator>

template<class Key, class T, class Compare, class Allocator>
class bst;

template<class Key, class T, class Compare, class Allocator, bool IsConst>
class bst_iterator {
private:
    using Node = typename bst<Key, T, Compare, Allocator>::Node;
    using node_ptr = std::conditional_t<IsConst, const Node*, Node*>;
    
    node_ptr current_;

    node_ptr findMin(node_ptr node) const;
    node_ptr findMax(node_ptr node) const;
    
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<const Key, T>;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t<IsConst, const value_type*, value_type*>;
    using reference = std::conditional_t<IsConst, const value_type&, value_type&>;
    
    bst_iterator() : current_(nullptr) {}
    explicit bst_iterator(node_ptr node) : current_(node) {}
    
    template<bool OtherConst>
    bst_iterator(const bst_iterator<Key, T, Compare, Allocator, OtherConst>& other,
                 std::enable_if_t<IsConst || !OtherConst>* = nullptr)
        : current_(other.current_) {}
    
    reference operator*() const;
    pointer operator->() const;
    
    bst_iterator& operator++();
    bst_iterator operator++(int);
    bst_iterator& operator--();
    bst_iterator operator--(int);
    
    template<bool OtherConst>
    bool operator==(const bst_iterator<Key, T, Compare, Allocator, OtherConst>& other) const;
    
    template<bool OtherConst>
    bool operator!=(const bst_iterator<Key, T, Compare, Allocator, OtherConst>& other) const;
    
    node_ptr node() const { return current_; }
};

#endif