# Forget new/delete, use Smart Pointers
| Smart Pointer     | Ownership            |
| ----------------- | -------------------- |
| `std::unique_ptr` | Single owner         |
| `std::shared_ptr` | Multiple owners      |
| `std::weak_ptr`   | Non-owning reference |

## Unique Ownership
`std:unique_ptr`
```c++
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(10);

    std::cout << *ptr << std::endl;
}
```
When `ptr` goes out of scope, delete memory automatically

### Ownership transfer
```C++
#include <memory>
#include <iostream>

void process(std::unique_ptr<int> p) {
    std::cout << *p << std::endl;
}

int main() {
    auto ptr = std::make_unique<int>(42);

    process(std::move(ptr));   // transfer ownership
}
```
Ater `std::move(ptr)`, ptr == nullptr, ownership move to `p`

## Shared ownership
`std::shared_ptr`
```c++
int main() {
    auto p1 = std::make_shared<int>(5);
    auto p2 = p1;

    std::cout << *p1 << std::endl;
}
```
```
reference count = 0   
p1 created → count = 1   
p2 copy → count = 2   
p1 destroyed → count = 1   
p2 destroyed → count = 0 → delete   
```
## Weak Pointer
### Circular References
```c++
#include <memory>

struct B;

struct A {
    std::shared_ptr<B> b;
};

struct B {
    std::shared_ptr<A> a;
};
```
```c++
int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b = b;
    b->a = a;
}
```
```
a owns A → count(A) = 1
b owns B → count(B) = 1

a->b owns B → count(B) = 2
b->a owns A → count(A) = 2
```
### Solution: `weak_ptr`
```c++
#include <memory>

struct B;

struct A {
    std::shared_ptr<B> b;
};

struct B {
    std::weak_ptr<A> a;   // weak pointer
};
```
```
shared_ptr → owns memory
weak_ptr   → observes memory
```
```
a owns A → count(A)=1
b owns B → count(B)=1

a->b owns B → count(B)=2
b->a weak → count(A) still =1
```
### Real Example
```c++
#include <memory>
#include <vector>

std::vector<std::weak_ptr<int>> cache;

void add(std::shared_ptr<int> obj) {
    cache.push_back(obj);
}
```
```c++
for (auto &w : cache) {
    if (auto obj = w.lock()) {
        // object still alive
    }
}
```
`weak_ptr` is used in:   
- Break circular references   
- Observer pattern
- Caches
