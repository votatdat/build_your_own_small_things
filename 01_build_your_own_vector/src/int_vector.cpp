#include "int_vector.hpp"

// default constructor
IntVector::IntVector() noexcept
    : data_{nullptr}, size_{0}, capacity_{0} {
}

// destructor
IntVector::~IntVector() {
    delete[] data_;
}

// copy constructor
IntVector::IntVector(const IntVector& other)
    : data_{nullptr}, size_{other.size_}, capacity_{other.capacity_} {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

// copy assignment operator
IntVector& IntVector::operator=(const IntVector& other) {
    if (this == &other) {
        return *this;
    }

    int* new_data = nullptr;

    if (other.capacity_ > 0) {
        new_data = new int[other.capacity_];
        for (std::size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }
    }

    delete[] data_; // initilized alr => must delete first
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

// move constructor
IntVector::IntVector(IntVector&& other) noexcept
    : data_{other.data_}, size_{other.size_}, capacity_{other.capacity_} {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

// move assignment operator
IntVector& IntVector::operator=(IntVector&& other) noexcept {
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

// internal re-allocate
void IntVector::reallocate(std::size_t new_capacity) {
    int* new_data = new int[new_capacity];

    for (std::size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

// capacity
std::size_t IntVector::size() const noexcept {
    return size_;
}
std::size_t IntVector::capacity() const noexcept {
    return capacity_;
}
bool IntVector::empty() const noexcept {
    return size_ == 0;
}

// element access
int& IntVector::operator[](std::size_t index) noexcept {
    return data_[index];
}
const int& IntVector::operator[](std::size_t index) const noexcept {
    return data_[index];
}

// int& at(std::size_t index);
// const int& at(std::size_t index) const;

// int& front();
// const int& front() const;

// int& back();
// const int& back() const;

// // modifiers
void IntVector::push_back(int value) {
    if (size_ == capacity_) {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    data_[size_] = value;
    size_++;
}
// void pop_back();

// void clear() noexcept;

// void reserve(std::size_t new_capacity);
// void resize(std::size_t new_size, int value = 0);

// // iterators
// int* begin() noexcept;
// const int* begin() const noexcept;
// const int* cbegin() const noexcept;

// int* end() noexcept;
// const int* end() const noexcept;
// const int* cend() const noexcept;