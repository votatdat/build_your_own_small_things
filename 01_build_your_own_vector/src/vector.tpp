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
