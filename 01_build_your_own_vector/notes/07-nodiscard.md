`[[nodiscard]]` is a C++ attribute (introduced in C++17) that tells the compiler:
```
The return value of this function should NOT be ignored.
```

### Without `[[nodiscard]]`:
```c++
int divide(int a, int b) {
    return a / b;
}

int main() {
    divide(10, 2);   // result ignored
}
```

### Using `[[nodiscard]]`:
```c++
[[nodiscard]] int divide(int a, int b) {
    return a / b;
}

int main() {
    divide(10, 2);  // compiler warning
}
```
Typical warning:
```
warning: ignoring return value of 'divide'
```