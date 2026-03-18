#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility> // std::move

template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reallocate(std::size_t new_capacity);

public:
    // ===== constructors / destructor =====
    Vector() noexcept;
    ~Vector();

    // Rule of 5
    Vector(const Vector& other);            // copy constructor
    Vector& operator=(const Vector& other); // copy assignment

    Vector(Vector&& other) noexcept;            // move constructor
    Vector& operator=(Vector&& other) noexcept; // move assignment

    // ===== capacity =====
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size, const T& value = T{}); // default construct T when expanding
    void clear() noexcept;

    // ===== element access =====
    T& operator[](std::size_t index) noexcept;
    const T& operator[](std::size_t index) const noexcept;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    // ===== modifiers =====
    void push_back(const T& value); // copy
    void push_back(T&& value);      // move

    void pop_back();

    void insert(std::size_t pos, const T& value);
    void erase(std::size_t pos);

    // ===== iterators =====
    T* begin() noexcept;
    const T* begin() const noexcept;
    const T* cbegin() const noexcept;

    T* end() noexcept;
    const T* end() const noexcept;
    const T* cend() const noexcept;
};

#include "vector.tpp"