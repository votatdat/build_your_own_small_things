#pragma once

#include <cstddef>

class IntVector {
private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reallocate(std::size_t new_capacity);

public:
    // constructors
    IntVector() noexcept;
    explicit IntVector(std::size_t count, int value = 0);

    // destructor
    ~IntVector();

    // copy semantics
    IntVector(const IntVector& other);
    IntVector& operator=(const IntVector& other);

    // move semantics
    IntVector(IntVector&& other) noexcept;
    IntVector& operator=(IntVector&& other) noexcept;

    // capacity
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    // element access
    int& operator[](std::size_t index) noexcept;
    const int& operator[](std::size_t index) const noexcept;

    int& at(std::size_t index);
    const int& at(std::size_t index) const;

    int& front();
    const int& front() const;

    int& back();
    const int& back() const;

    // modifiers
    void push_back(int value);
    void pop_back();

    void clear() noexcept;

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size, int value = 0);

    // iterators
    int* begin() noexcept;
    const int* begin() const noexcept;
    const int* cbegin() const noexcept;

    int* end() noexcept;
    const int* end() const noexcept;
    const int* cend() const noexcept;
};