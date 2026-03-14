Should read [01-memory-ownership.md](./01-memory-ownership.md) first to have a sense of Smart Pointers and memory onwership

---
## 1. The Problem Move Semantics Solves
```c++
#include <vector>

std::vector<int> createVector() {
    std::vector<int> v = {1,2,3,4,5};
    return v;
}

int main() {
    std::vector<int> data = createVector();
}
```
```
createVector()
   |
   | copy = expensive memory operation when the vector is large
   ↓
main()
```
### The idea of Move
```
A owns memory
↓ move
B owns memory
A becomes empty
```
## 2. Move example
```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {1,2,3,4};

    std::vector<int> b = std::move(a);

    std::cout << a.size() << std::endl; // usually 0
}
```
```
a owns memory
↓ move
b owns memory
a becomes empty
```
### So what `std:move` does?
**`std::move` DOES NOT move anything, it only casts to an `rvalue` reference.**

## 3. Move constructor
```c++
#include <iostream>

class Buffer {
private:
    int* data;
    size_t size;

public:

    // Constructor
    Buffer(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Constructor\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        std::cout << "Destructor\n";
    }

    // Move Constructor
    Buffer(Buffer&& other) noexcept {
        std::cout << "Move Constructor\n";

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
    }

    // Move Assignment Operator
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "Move Assignment\n";

        if (this != &other) {
            delete[] data;        // release current resource

            data = other.data;    // take ownership
            size = other.size;

            other.data = nullptr; // prevent double free
            other.size = 0;
        }

        return *this;
    }

    // Utility function
    void printSize() const {
        std::cout << "size = " << size << std::endl;
    }
};
```
Move flow:   
```
other.data → transferred
other.data = nullptr
```
## 4. Lvalue vs Rvalue
### Lvalue
```
has a name
```
Example:
```c++
int x = 10;
```
x is an lvalue.   
### Rvalue
```
temporary object
```
Example:
```c++
10
x + y
createObject()
```
### Rvalue reference
Syntax:   
```c++
T&&
```
Example:
```c++
void process(Buffer&& b);
```
This means:
```
temporary object allowed
```