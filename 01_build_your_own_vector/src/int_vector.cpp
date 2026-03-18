#include "int_vector.hpp"

#include <stdexcept>

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

    for (std::size_t i = 0; i < size_; ++i) {
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

int& IntVector::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("IntVector::at: index out of range");
    }
    return data_[index];
}
const int& IntVector::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("IntVector::at: index out of range");
    }
    return data_[index];
}

int& IntVector::front() {
    if (empty()) {
        throw std::out_of_range("IntVector::front: vector is empty");
    }
    return data_[0];
}
const int& IntVector::front() const {
    if (empty()) {
        throw std::out_of_range("IntVector::front: vector is empty");
    }
    return data_[0];
}

int& IntVector::back() {
    if (empty()) {
        throw std::out_of_range("IntVector::back: vector is empty");
    }
    return data_[size_ - 1];
}
const int& IntVector::back() const {
    if (empty()) {
        throw std::out_of_range("IntVector::back: vector is empty");
    }
    return data_[size_ - 1];
}

// modifiers
void IntVector::push_back(int value) {
    if (size_ == capacity_) {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    data_[size_] = value;
    ++size_;
}

void IntVector::pop_back() {
    if (empty()) {
        throw std::out_of_range("IntVector::pop_back: vector is empty");
    }
    --size_;
}

void IntVector::clear() noexcept {
    size_ = 0;
}

void IntVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    reallocate(new_capacity);
}

void IntVector::resize(std::size_t new_size, int value) {
    if (new_size > size_) {
        if (new_size > capacity_) {
            reallocate(new_size);
        }
        for (std::size_t i = size_; i < new_size; ++i) {
            data_[i] = value;
        }
    }
    size_ = new_size;
}

// iterator
int* IntVector::begin() noexcept {
    return data_;
}
const int* IntVector::begin() const noexcept {
    return data_;
}
const int* IntVector::cbegin() const noexcept {
    return data_;
}

int* IntVector::end() noexcept {
    return data_ + size_;
}
const int* IntVector::end() const noexcept {
    return data_ + size_;
}
const int* IntVector::cend() const noexcept {
    return data_ + size_;
}

void IntVector::insert(std::size_t pos, int value) {
    if (pos > size_) {
        throw std::out_of_range("IntVector::insert: position out of range");
    }

    if (size_ == capacity_) {
        const std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }

    for (std::size_t i = size_; i > pos; --i) {
        data_[i] = data_[i - 1];
    }

    data_[pos] = value;
    ++size_;
}

void IntVector::erase(std::size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("IntVector::erase: position out of range");
    }

    for (std::size_t i = pos; i + 1 < size_; ++i) {
        data_[i] = data_[i + 1];
    }

    --size_;
}