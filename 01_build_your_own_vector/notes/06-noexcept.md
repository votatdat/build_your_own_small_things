
`noexcept` is a keyword that tells the compiler:
```
this function will NOT throw exceptions
```
Example:
```c++
void process() noexcept {
    std::cout << "Processing\n";
}
```
means:
```
process() guarantees it will not throw exceptions
```

`noexcept` is critical for move constructors. Modern C++ guideline: **Move constructors should almost always be noexcept**.
```c++
class Buffer {
public:
    Buffer(Buffer&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }
};
```

### Practical Modern C++ Pattern:
```c++
class Order {
public:
    Order() = default;
    Order(Order&&) noexcept = default;
    Order& operator=(Order&&) noexcept = default;
};
```