#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>
#include <memory>
#include <stdexcept>

template<typename T>
class Vector {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

    Vector();
    explicit Vector(size_type count);
    Vector(size_type count, const T& value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
    
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data() noexcept;
    const T* data() const noexcept;
    
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();
    
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    iterator insert(const_iterator pos, const T& value);
    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    void resize(size_type count);
    void resize(size_type count, const T& value);
    void reverse();

private:
    T* data_;
    size_t size_;
    size_t capacity_;
};


template<>
class Vector<bool> {
public:
    using value_type = bool;
    using size_type = size_t;

private:
    unsigned char* data_;
    size_t size_;
    size_t capacity_;
    static const size_t BITS_PER_CHAR = 8;

    class reference {
    private:
        unsigned char* byte_;
        unsigned char mask_;
        
    public:
        reference(unsigned char* byte, size_t bit_pos);
        reference& operator=(bool value);
        reference& operator=(const reference& other);
        operator bool() const;
    };

    void set_bit(size_type pos, bool value);

public:
    Vector();
    explicit Vector(size_type count);
    Vector(size_type count, bool value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
    
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    
    reference operator[](size_type pos);
    bool operator[](size_type pos) const;
    bool front() const;
    bool back() const;
    unsigned char* data() noexcept;
    const unsigned char* data() const noexcept;
    
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();
    
    void push_back(bool value);
    void pop_back();
    void insert(size_type pos, bool value);
    void resize(size_type count);
    void resize(size_type count, bool value);
    void reverse();
};

#include "Vector.hpp"

#endif