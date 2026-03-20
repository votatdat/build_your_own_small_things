## 1. The Problem We Want to Solve
Suppose we write a generic function:
```c++
template<typename T>
void process(T arg) {
    // do something
}
```
Problem:
```
arg is always copied
```
Even if we pass:
```c++
process(std::string("hello"));
```
We may incur unnecessary copies.

## 2. Step 1 — Use References
```c++
template<typename T>
void process(T& arg) {
    // lvalue reference
}
```
Problem:
```
cannot accept rvalues
```
Example:
```c++
process(std::string("hello")); // ❌ error
```
## 3. Step 2 — Use rvalue reference
```c++
template<typename T>
void process(T&& arg) {
    // rvalue reference?
}
```
Now it works for:
```c++
process(std::string("hello")); // OK
```
BUT here's the twist:
```
T&& in templates is NOT always rvalue reference
```
This is called a **forwarding reference (universal reference)**.

## 4. The Magic: Forwarding Reference
```c++
template<typename T>
void process(T&& arg);
```
Behavior:
| Argument | T deduced as | arg type     |
| -------- | ------------ | ------------ |
| lvalue   | `T&`         | `T& && → T&` |
| rvalue   | `T`          | `T&&`        |

So:
```c++
std::string s = "hello";

process(s);              // lvalue
process(std::move(s));   // rvalue
```

## 5. The Problem Now
Inside the function:
```c++
template<typename T>
void process(T&& arg) {
    use(arg);
}
```
Problem:
```
arg is ALWAYS treated as lvalue
```
Even if it was passed as rvalue.

## 6. Why?
Because:
```
named variables are always lvalues
```
So: **arg is an lvalue, even if originally rvalue.**

## 7. Solution: `std::forward`
```c++
template<typename T>
void process(T&& arg) {
    use(std::forward<T>(arg));
}
```
This preserves:
```
lvalue stays lvalue
rvalue stays rvalue
```

## 8. What `std::forward` Does
Conceptually:
```
if T is lvalue reference → return lvalue
if T is value → return rvalue
```

## 9. Full Example
```c++
#include <iostream>
#include <utility>

void handle(int& x) {
    std::cout << "lvalue\n";
}

void handle(int&& x) {
    std::cout << "rvalue\n";
}

template<typename T>
void process(T&& arg) {
    handle(std::forward<T>(arg));
}

int main() {
    int x = 10;

    process(x);           // lvalue
    process(20);          // rvalue
}
```
Output:
```
lvalue
rvalue
```

## 10. Without std::forward (Bug)
```c++
template<typename T>
void process(T&& arg) {
    handle(arg);
}
```
Output:
```
lvalue
lvalue
```
❌ WRONG

Because `arg` is **always lvalue inside the function**.

## 11. Key Insight
```
std::move → force rvalue
std::forward → preserve original value category
```

## 12. Perfect Forwarding
Definition:
```
Perfect forwarding = passing arguments exactly as received (no copy, no change)
```
Pattern:
```c++
template<typename T>
void wrapper(T&& arg) {
    target(std::forward<T>(arg));
}
```

## 13. Real Example
**Factory function**
```c++
template<typename T, typename... Args>
T* create(Args&&... args) {
    return new T(std::forward<Args>(args)...);
}
```
Usage:
```c++
auto obj = create<std::string>(10, 'a');
```
This perfectly forwards arguments to constructor.

## 14. STL Example
`std::make_unique`:
```c++
template<class T, class... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```
This is perfect forwarding in real life.

## 15. Why This Matters
Without perfect forwarding:
```
extra copies
extra allocations
slower code
```
With perfect forwarding:
```
zero-cost abstraction
maximum performance
```
This is critical in:
```
order book updates
pricing engines
data pipelines
message passing
```

## 16. Common Mistakes
❌ Using `std::move` instead of `std::forward`
```c++
target(std::move(arg)); // WRONG
```
This forces everything to rvalue.

❌ Forgetting forwarding
```c++
target(arg); // loses rvalue
```

## 17. Summary
| Concept            | Meaning                           |
| ------------------ | --------------------------------- |
| `T&&` (template)   | forwarding reference              |
| `std::move`        | convert to rvalue                 |
| `std::forward`     | preserve value type               |
| perfect forwarding | pass argument exactly as received |

## 18. Mental Model
```
input → wrapper → output

lvalue → stays lvalue
rvalue → stays rvalue
```

## 19. One-Liner Rule
Use `std::forward<T>(arg)` when forwarding template arguments
