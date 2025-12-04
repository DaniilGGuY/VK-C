#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <functional>
#include <stdexcept>
#include <iterator>
#include "bst_iterator.h"

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
>
class bst {
private:
    struct Node {
        std::pair<const Key, T> data;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(const Key& key, const T& value, Node* parent = nullptr)
            : data(key, value), left(nullptr), right(nullptr), parent(parent) {}
    };

    template<class K, class V, class C, class A, bool IC>
    friend class bst_iterator;

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using key_compare = Compare;
    using allocator_type = Allocator;
    
    using iterator = bst_iterator<Key, T, Compare, Allocator, false>;
    using const_iterator = bst_iterator<Key, T, Compare, Allocator, true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    Node* root_;
    size_type size_;
    Compare comp_;
    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    node_allocator alloc_;

    Node* createNode(const Key& key, const T& value, Node* parent = nullptr);
    void destroyNode(Node* node);
    Node* copyTree(Node* node, Node* parent);
    void destroyTree(Node* node);
    Node* findNode(const Key& key) const;
    Node* insertNode(const Key& key, const T& value);
    void eraseNode(Node* node);
    Node* getMinNode() const;
    Node* getMaxNode() const;

public:
    bst() : root_(nullptr), size_(0) {}
    explicit bst(const Compare& comp) : root_(nullptr), size_(0), comp_(comp) {}
    
    bst(const bst& other);
    bst(bst&& other) noexcept;
    ~bst();
    
    bst& operator=(const bst& other);
    bst& operator=(bst&& other) noexcept;
    
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    
    T& operator[](const Key& key);
    T& at(const Key& key);
    const T& at(const Key& key) const;
    
    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    size_type erase(const Key& key);
    void clear();
    
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    bool contains(const Key& key) const;
    
    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
};

#include "bst_iterator.hpp"
#include "binary_tree.hpp"

#endif