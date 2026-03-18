## 1. What is a Template?
Definition:
```
Template = blueprint for generating code for different types
```
Instead of writing:
```c++
int add(int a, int b);
double add(double a, double b);
```
You write one version:
```c++
template<typename T>
T add(T a, T b) {
    return a + b;
}
```

## 2. Basic Function Template
```c++
#include <iostream>

template<typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(2, 3) << std::endl;        // int
    std::cout << add(2.5, 3.5) << std::endl;    // double
}
```
Compiler generates:
```c++
add<int>
add<double>
```

## 3. `typename` vs `class`
Both are equivalent here:
```c++
template<typename T>
template<class T>
```
Modern C++ prefers: **typename**

## 4. Class Template
Example: simplified vector
```c++
template<typename T>
class MyVector {
private:
    T* data_;
    size_t size_;

public:
    MyVector(size_t size) : size_(size) {
        data_ = new T[size];
    }

    ~MyVector() {
        delete[] data_;
    }

    T& operator[](size_t i) {
        return data_[i];
    }
};
```
Usage:
```c++
MyVector<int> v1(10);
MyVector<double> v2(5);
```
Compiler generates:
```c++
MyVector<int>
MyVector<double>
```

## 5. Why Templates Matter
Without templates: duplicate code for each type   
With templates: write once → works for all types

This is how STL works:
```c++
std::vector<int>
std::vector<double>
std::vector<Order>
```

## 6. Template Instantiation
**Templates are compiled when used.**   
Example:
```c++
add(2, 3);
```
Compiler generates:
```c++
int add<int>(int, int);
```

## 7. Multiple Template Parameters
```c++
template<typename T, typename U>
auto add(T a, U b) {
    return a + b;
}
```
Usage:
```c++
add(2, 3.5);   // int + double
```

## 8. Template Specialization
You can customize behavior for specific types.

Example:
```c++
template<typename T>
void print(T value) {
    std::cout << value << std::endl;
}
```
Special case:
```c++
template<>
void print<bool>(bool value) {
    std::cout << (value ? "true" : "false") << std::endl;
}
```

## 9. Template and Inline (Performance)
Templates are usually:
```
compiled at compile-time
often inlined
no runtime overhead
```

This is why C++ templates are called:
```
zero-cost abstraction
```

## 10. Example: Generic Swap
```c++
template<typename T>
void swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}
```
Works for:
```
int
double
std::string
custom classes
```

## 11. Templates + Move Semantics
Modern C++ templates often use:
```c++
std::move
std::forward
```
Example:
```c++
template<typename T>
void setValue(T&& value) {
    data_ = std::forward<T>(value);
}
```
This is called:
```
perfect forwarding
```

## 12. Templates and Type Deduction
Compiler can deduce types:
```c++
add(2, 3);
```
No need to write:
```c++
add<int>(2, 3);
```

## 13. Key STL Example
```c++
std::vector<int>
```
Internally:
```c++
template<typename T>
class vector;
```
So:
```c++
vector<int>
vector<double>
vector<Order>
```
all use the same template.

## 14. Common Template Syntax
| Syntax                 | Meaning          |
| ---------------------- | ---------------- |
| `template<typename T>` | declare template |
| `T`                    | generic type     |
| `T&`                   | reference to T   |
| `T&&`                  | rvalue reference |
| `template<>`           | specialization   |

## 15. Common Beginner Pitfalls
### 1. Templates must be in header files
Because they are compiled when used.
### 2. Type must support operations
Example:
```c++
T add(T a, T b) {
    return a + b;
}
```
Requires: **T must support operator+**
### 3. Error messages are complex
Template errors can be long and confusing.

## 16. Modern C++ Improvement: Concepts (C++20)
You can constrain templates:
```c++
#include <concepts>

template<std::integral T>
T add(T a, T b) {
    return a + b;
}
```
Now only **integers are allowed**.

## 17. Summary
Templates allow:
```
generic programming
code reuse
zero-cost abstraction
high performance
```
Core idea:
```
write once → generate many types at compile time
```