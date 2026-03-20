#pragma once
#include "vector.hpp"

#include <stdexcept>

// default constructor
template <typename T>
Vector<T>::Vector() noexcept
    : data_{nullptr}, size_{0}, capacity_{0} {
}

// destructor
template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

// copy semantics
template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : data_{nullptr}, size_{other.size_}, capacity_{other.capacity_} {
    if (capacity_ > 0) {
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) {
        return *this;
    }

    T* new_data = nullptr;

    if (other.capacity_ > 0) {
        new_data = new T[other.capacity_];
        for (std::size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }
    }

    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

// move semantics
template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
    : data_{other.data_}, size_{other.size_}, capacity_{other.capacity_} {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

template <typename T>
void Vector<T>::reallocate(std::size_t new_capacity) {
    if (new_capacity < size_) {
        throw std::length_error("Vector::reallocate: new capacity is smaller than size");
    }

    T* new_data = new T[new_capacity];

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

// ===== capacity =====
template <typename T>
std::size_t Vector<T>::size() const noexcept {
    return size_;
}
template <typename T>
std::size_t Vector<T>::capacity() const noexcept {
    return capacity_;
}
template <typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

// ===== element access =====
template <typename T>
T& Vector<T>::operator[](std::size_t index) noexcept {
    return data_[index];
}
template <typename T>
const T& Vector<T>::operator[](std::size_t index) const noexcept {
    return data_[index];
}

template <typename T>
T& Vector<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Vector::at: index out of range");
    }
    return data_[index];
}
template <typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Vector::at: index out of range");
    }
    return data_[index];
}

template <typename T>
T& Vector<T>::front() {
    if (empty()) {
        throw std::out_of_range("Vector::front: vector is empty");
    }
    return data_[0];
}
template <typename T>
const T& Vector<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Vector::front: vector is empty");
    }
    return data_[0];
}

template <typename T>
T& Vector<T>::back() {
    if (empty()) {
        throw std::out_of_range("Vector::back: vector is empty");
    }
    return data_[size_ - 1];
}
template <typename T>
const T& Vector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Vector::back: vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
void Vector<T>::reserve(std::size_t new_capacity) {
    if (new_capacity > capacity_) {
        reallocate(new_capacity);
    }
}
template <typename T>
void Vector<T>::resize(std::size_t new_size, const T& value) {
    if (new_size < size_) {
        size_ = new_size;
        return;
    }

    if (new_size > capacity_) {
        reallocate(new_size);
    }

    for (std::size_t i = size_; i < new_size; ++i) {
        data_[i] = value;
    }

    size_ = new_size;
}
template <typename T>
void Vector<T>::clear() noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = T{};
    }
    size_ = 0;
}

// // ===== modifiers =====
template <typename T>
void Vector<T>::push_back(const T& value) { // copy
    if (size_ == capacity_) {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    data_[size_] = value;
    ++size_;
}
template <typename T>
void Vector<T>::push_back(T&& value) { // move
    if (size_ == capacity_) {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    data_[size_] = std::move(value);
    ++size_;
}

template <typename T>
void Vector<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Vector::pop_back: vector is empty");
    }
    --size_;
    data_[size_] = T{};
}

template <typename T>
void Vector<T>::insert(std::size_t pos, const T& value) {
    if (pos > size_) {
        throw std::out_of_range("Vector::insert: position out of range");
    }
    if (size_ == capacity_) {
        const std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    for (std::size_t i = size_; i > pos; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[pos] = value;
    ++size_;
}

template <typename T>
void Vector<T>::erase(std::size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("Vector::erase: position out of range");
    }
    for (std::size_t i = pos; i + 1 < size_; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
    data_[size_] = T{};
}

// ===== iterators =====
template <typename T>
T* Vector<T>::begin() noexcept {
    return data_;
}
template <typename T>
const T* Vector<T>::begin() const noexcept {
    return data_;
}
template <typename T>
const T* Vector<T>::cbegin() const noexcept {
    return data_;
}

template <typename T>
T* Vector<T>::end() noexcept {
    return data_ + size_;
}
template <typename T>
const T* Vector<T>::end() const noexcept {
    return data_ + size_;
}
template <typename T>
const T* Vector<T>::cend() const noexcept {
    return data_ + size_;
}