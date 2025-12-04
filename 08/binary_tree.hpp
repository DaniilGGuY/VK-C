#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

template<class Key, class T, class Compare, class Allocator>
bst<Key, T, Compare, Allocator>::bst(const bst& other)
    : root_(nullptr), size_(0), comp_(other.comp_), alloc_(other.alloc_) {
    root_ = copyTree(other.root_, nullptr);
    size_ = other.size_;
}

template<class Key, class T, class Compare, class Allocator>
bst<Key, T, Compare, Allocator>::bst(bst&& other) noexcept 
    : root_(other.root_), size_(other.size_), comp_(std::move(other.comp_)), alloc_(std::move(other.alloc_)) {
    other.root_ = nullptr;
    other.size_ = 0;
}

template<class Key, class T, class Compare, class Allocator>
bst<Key, T, Compare, Allocator>::~bst() {
    clear();
}

template<class Key, class T, class Compare, class Allocator>
bst<Key, T, Compare, Allocator>&
bst<Key, T, Compare, Allocator>::operator=(const bst& other) {
    if (this != &other) {
        clear();
        comp_ = other.comp_;
        alloc_ = other.alloc_;
        root_ = copyTree(other.root_, nullptr);
        size_ = other.size_;
    }
    return *this;
}

template<class Key, class T, class Compare, class Allocator>
bst<Key, T, Compare, Allocator>&
bst<Key, T, Compare, Allocator>::operator=(bst&& other) noexcept {
    if (this != &other) {
        clear();
        root_ = other.root_;
        size_ = other.size_;
        comp_ = std::move(other.comp_);
        alloc_ = std::move(other.alloc_);
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::createNode(const Key& key, const T& value, Node* parent) {
    Node* node = new Node(key, value, parent);
    return node;
}

template<class Key, class T, class Compare, class Allocator>
void bst<Key, T, Compare, Allocator>::destroyNode(Node* node) {
    delete node;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::copyTree(Node* node, Node* parent) {
    if (!node) return nullptr;
    
    Node* newNode = createNode(node->data.first, node->data.second, parent);
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
}

template<class Key, class T, class Compare, class Allocator>
void bst<Key, T, Compare, Allocator>::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        destroyNode(node);
    }
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::findNode(const Key& key) const {
    Node* current = root_;
    while (current) {
        if (comp_(key, current->data.first)) {
            current = current->left;
        } else if (comp_(current->data.first, key)) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::insertNode(const Key& key, const T& value) {
    if (!root_) {
        root_ = createNode(key, value);
        size_ = 1;
        return root_;
    }

    Node* current = root_;
    Node* parent = nullptr;
    
    while (current) {
        parent = current;
        if (comp_(key, current->data.first)) {
            current = current->left;
        } else if (comp_(current->data.first, key)) {
            current = current->right;
        } else {
            // Ключ уже существует
            current->data.second = value;
            return current;
        }
    }

    Node* newNode = createNode(key, value, parent);
    if (comp_(key, parent->data.first)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    size_++;
    return newNode;
}

template<class Key, class T, class Compare, class Allocator>
void bst<Key, T, Compare, Allocator>::eraseNode(Node* node) {
    if (!node) return;

    if (!node->left && !node->right) {
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = nullptr;
            else node->parent->right = nullptr;
        } else {
            root_ = nullptr;
        }
        destroyNode(node);
    } else if (node->left && !node->right) {
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = node->left;
            else node->parent->right = node->left;
        } else {
            root_ = node->left;
        }
        node->left->parent = node->parent;
        destroyNode(node);
    } else if (!node->left && node->right) {
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = node->right;
            else node->parent->right = node->right;
        } else {
            root_ = node->right;
        }
        node->right->parent = node->parent;
        destroyNode(node);
    } else {
        Node* successor = node->right;
        while (successor->left) {
            successor = successor->left;
        }
        
        // Копируем данные
        const_cast<Key&>(node->data.first) = successor->data.first;
        node->data.second = successor->data.second;
        
        // Удаляем преемника
        eraseNode(successor);
        return;
    }
    
    size_--;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::getMinNode() const {
    if (!root_) return nullptr;
    Node* current = root_;
    while (current->left) {
        current = current->left;
    }
    return current;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::Node*
bst<Key, T, Compare, Allocator>::getMaxNode() const {
    if (!root_) return nullptr;
    Node* current = root_;
    while (current->right) {
        current = current->right;
    }
    return current;
}

// Реализация публичных методов
template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::iterator
bst<Key, T, Compare, Allocator>::begin() noexcept {
    return iterator(getMinNode());
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::const_iterator
bst<Key, T, Compare, Allocator>::begin() const noexcept {
    return const_iterator(getMinNode());
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::iterator
bst<Key, T, Compare, Allocator>::end() noexcept {
    return iterator(nullptr);
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::const_iterator
bst<Key, T, Compare, Allocator>::end() const noexcept {
    return const_iterator(nullptr);
}

template<class Key, class T, class Compare, class Allocator>
T& bst<Key, T, Compare, Allocator>::operator[](const Key& key) {
    Node* node = findNode(key);
    if (node) {
        return node->data.second;
    }
    return insertNode(key, T())->data.second;
}

template<class Key, class T, class Compare, class Allocator>
T& bst<Key, T, Compare, Allocator>::at(const Key& key) {
    Node* node = findNode(key);
    if (!node) throw std::out_of_range("Key not found");
    return node->data.second;
}

template<class Key, class T, class Compare, class Allocator>
const T& bst<Key, T, Compare, Allocator>::at(const Key& key) const {
    Node* node = findNode(key);
    if (!node) throw std::out_of_range("Key not found");
    return node->data.second;
}

template<class Key, class T, class Compare, class Allocator>
std::pair<typename bst<Key, T, Compare, Allocator>::iterator, bool>
bst<Key, T, Compare, Allocator>::insert(const value_type& value) {
    Node* existing = findNode(value.first);
    if (existing) {
        existing->data.second = value.second;
        return std::make_pair(iterator(existing), false);
    }
    Node* newNode = insertNode(value.first, value.second);
    return std::make_pair(iterator(newNode), true);
}

template<class Key, class T, class Compare, class Allocator>
void bst<Key, T, Compare, Allocator>::erase(iterator pos) {
    if (pos != end()) {
        eraseNode(const_cast<Node*>(pos.node()));
    }
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::size_type
bst<Key, T, Compare, Allocator>::erase(const Key& key) {
    Node* node = findNode(key);
    if (node) {
        eraseNode(node);
        return 1;
    }
    return 0;
}

template<class Key, class T, class Compare, class Allocator>
void bst<Key, T, Compare, Allocator>::clear() {
    destroyTree(root_);
    root_ = nullptr;
    size_ = 0;
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::iterator
bst<Key, T, Compare, Allocator>::find(const Key& key) {
    return iterator(findNode(key));
}

template<class Key, class T, class Compare, class Allocator>
typename bst<Key, T, Compare, Allocator>::const_iterator
bst<Key, T, Compare, Allocator>::find(const Key& key) const {
    return const_iterator(findNode(key));
}

template<class Key, class T, class Compare, class Allocator>
bool bst<Key, T, Compare, Allocator>::contains(const Key& key) const {
    return findNode(key) != nullptr;
}

#endif