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
