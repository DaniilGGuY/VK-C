#include "Vector.h"

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type count) : size_(count), capacity_(count) {
    data_ = new T[capacity_];
}

template<typename T>
Vector<T>::Vector(size_type count, const T& value) : size_(count), capacity_(count) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
    return data_[pos];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
    return data_[pos];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
    return data_[0];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return data_[0];
}

template<typename T>
typename Vector<T>::reference Vector<T>::back() {
    return data_[size_ - 1];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return data_[size_ - 1];
}

template<typename T>
T* Vector<T>::data() noexcept {
    return data_;
}

template<typename T>
const T* Vector<T>::data() const noexcept {
    return data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return data_;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return data_ + size_;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return data_ + size_;
}

template<typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return SIZE_MAX / sizeof(T);
}

template<typename T>
void Vector<T>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        T* new_data = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template<typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& value) {
    size_t index = pos - data_;
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
    ++size_;
    return data_ + index;
}

template<typename T>
template<typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
    size_t index = pos - data_;
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = T(std::forward<Args>(args)...);
    ++size_;
    return data_ + index;
}

template<typename T>
void Vector<T>::resize(size_type count) {
    if (count > capacity_) {
        reserve(count);
    }
    size_ = count;
}

template<typename T>
void Vector<T>::resize(size_type count, const T& value) {
    if (count > size_) {
        if (count > capacity_) {
            reserve(count);
        }
        for (size_t i = size_; i < count; ++i) {
            data_[i] = value;
        }
    }
    size_ = count;
}

template<typename T>
void Vector<T>::reverse() {
    for (size_t i = 0; i < size_ / 2; ++i) {
        std::swap(data_[i], data_[size_ - i - 1]);
    }
}

Vector<bool>::reference::reference(unsigned char* byte, size_t bit_pos) 
    : byte_(byte), mask_(1 << bit_pos) {}

Vector<bool>::reference& Vector<bool>::reference::operator=(bool value) {
    if (value) {
        *byte_ |= mask_;
    } else {
        *byte_ &= ~mask_;
    }
    return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=(const reference& other) {
    return *this = static_cast<bool>(other);
}

Vector<bool>::reference::operator bool() const {
    return (*byte_ & mask_) != 0;
}

void Vector<bool>::set_bit(size_type pos, bool value) {
    size_t byte_index = pos / BITS_PER_CHAR;
    size_t bit_index = pos % BITS_PER_CHAR;
    if (value) {
        data_[byte_index] |= (1 << bit_index);
    } else {
        data_[byte_index] &= ~(1 << bit_index);
    }
}

Vector<bool>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

Vector<bool>::Vector(size_type count) : size_(count), capacity_((count + BITS_PER_CHAR - 1) / BITS_PER_CHAR) {
    data_ = new unsigned char[capacity_]{};
}

Vector<bool>::Vector(size_type count, bool value) : size_(count), capacity_((count + BITS_PER_CHAR - 1) / BITS_PER_CHAR) {
    data_ = new unsigned char[capacity_]{};
    if (value) {
        for (size_t i = 0; i < size_; ++i) {
            set_bit(i, true);
        }
    }
}

Vector<bool>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new unsigned char[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = other.data_[i];
    }
}

Vector<bool>::Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector<bool>::~Vector() {
    delete[] data_;
}

Vector<bool>& Vector<bool>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new unsigned char[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

Vector<bool>& Vector<bool>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

Vector<bool>::reference Vector<bool>::operator[](size_type pos) {
    return reference(data_ + pos / BITS_PER_CHAR, pos % BITS_PER_CHAR);
}

bool Vector<bool>::operator[](size_type pos) const {
    return (data_[pos / BITS_PER_CHAR] >> (pos % BITS_PER_CHAR)) & 1;
}

bool Vector<bool>::front() const {
    return (*this)[0];
}

bool Vector<bool>::back() const {
    return (*this)[size_ - 1];
}

unsigned char* Vector<bool>::data() noexcept {
    return data_;
}

const unsigned char* Vector<bool>::data() const noexcept {
    return data_;
}

bool Vector<bool>::empty() const noexcept {
    return size_ == 0;
}

Vector<bool>::size_type Vector<bool>::size() const noexcept {
    return size_;
}

Vector<bool>::size_type Vector<bool>::max_size() const noexcept {
    return SIZE_MAX / sizeof(bool);
}

void Vector<bool>::reserve(size_type new_cap) {
    size_type new_cap_bytes = (new_cap + BITS_PER_CHAR - 1) / BITS_PER_CHAR;
    if (new_cap_bytes > capacity_) {
        unsigned char* new_data = new unsigned char[new_cap_bytes]{};
        for (size_t i = 0; i < capacity_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap_bytes;
    }
}

Vector<bool>::size_type Vector<bool>::capacity() const noexcept {
    return capacity_ * BITS_PER_CHAR;
}

void Vector<bool>::shrink_to_fit() {
    size_type required_bytes = (size_ + BITS_PER_CHAR - 1) / BITS_PER_CHAR;
    if (capacity_ > required_bytes) {
        unsigned char* new_data = new unsigned char[required_bytes]{};
        for (size_t i = 0; i < required_bytes; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = required_bytes;
    }
}

void Vector<bool>::push_back(bool value) {
    if (size_ >= capacity()) {
        reserve(capacity() == 0 ? 1 : capacity() * 2);
    }
    set_bit(size_++, value);
}

void Vector<bool>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector<bool>::insert(size_type pos, bool value) {
    if (size_ >= capacity()) {
        reserve(capacity() == 0 ? 1 : capacity() * 2);
    }
    for (size_t i = size_; i > pos; --i) {
        set_bit(i, (*this)[i - 1]);
    }
    set_bit(pos, value);
    ++size_;
}

void Vector<bool>::resize(size_type count) {
    resize(count, false);
}

void Vector<bool>::resize(size_type count, bool value) {
    if (count > capacity()) {
        reserve(count);
    }
    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            set_bit(i, value);
        }
    }
    size_ = count;
}

void Vector<bool>::reverse() {
    for (size_t i = 0; i < size_ / 2; ++i) {
        bool temp = (*this)[i];
        set_bit(i, (*this)[size_ - i - 1]);
        set_bit(size_ - i - 1, temp);
    }
}