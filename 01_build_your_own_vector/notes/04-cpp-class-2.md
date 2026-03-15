# Anatomy of a modern C++ class

## 1. 1. Full Example Class
```c++
#include <iostream>

class Order {
private:
    int id;                 // data member
    double price;

    static int orderCount;  // static member

public:

    // constructor
    Order(int id, double price) : id(id), price(price) {
        orderCount++;
    }

    // destructor
    ~Order() {
        orderCount--;
    }

    // copy constructor
    Order(const Order& other) = default;

    // copy assignment
    Order& operator=(const Order& other) = default;

    // move constructor
    Order(Order&& other) noexcept = default;

    // move assignment
    Order& operator=(Order&& other) noexcept = default;

    // member function
    void print() const {
        std::cout << "Order " << id << " price " << price << std::endl;
    }

    // static function
    static int getOrderCount() {
        return orderCount;
    }

    // friend function
    friend std::ostream& operator<<(std::ostream& os, const Order& o);
};

int Order::orderCount = 0;

std::ostream& operator<<(std::ostream& os, const Order& o) {
    os << "Order(" << o.id << ", " << o.price << ")";
    return os;
}
```

## 2. Data Members
```c++
private:
    int id;
    double price;
```
**Each instance has its own copy.**   
Example:
```c++
Order o1(1,100);
Order o2(2,200);
```
Memory:
```
o1 → id=1 price=100
o2 → id=2 price=200
```

## 3. Access Specifiers
| Keyword     | Meaning                      |
| ----------- | ---------------------------- |
| `public`    | accessible everywhere        |
| `private`   | accessible only inside class |
| `protected` | accessible in subclasses     |


## 4. Constructors
**Constructor initializes the object.**
```c++
Order(int id, double price) : id(id), price(price) {}
```
This syntax is called an **initializer list**.

Better than:
```c++
Order(int id, double price) {
    this->id = id;
}
```
Initializer list:
```
construct members directly
```
instead of:
```
construct → assign
```

## 5. Destructor

**Destructor runs when object is destroyed**.
```c++
~Order()
```
Used for:
```
releasing memory
closing files
releasing locks
```
Example:
```c++
{
    Order o(1,100);
}
```
When block ends:
```
destructor runs automatically
```
This is **RAII**.

## 6. Copy Constructor

**Defines how objects are copied**.
```c++
Order(const Order& other) = default;
```
Example:
```c++
Order a(1,100);
Order b = a;
```
Result:
```
b.id = a.id
b.price = a.price
```

## 7. Move Constructor
**Handles ownership transfer**.
```c++
Order(Order&& other) noexcept = default;
```
Example:
```c++
Order b = std::move(a);
```
Move semantics **avoids expensive copies**.

## 8. Member Functions
**Functions belonging to the class.**
```c++
void print() const
```
**const** means: **function does not modify object**   
Example:
```c++
Order o(1,100);
o.print();
```

## 9. Static Members
**Shared by all objects.**
```c++
static int orderCount;
```
**Only one copy exists.**

Memory:
```
Order class
-----------
orderCount (shared)
```
Usage:
```c++
Order::getOrderCount();
```

## 10. Friend Functions
**Allows external functions to access private members.**
```c++
friend std::ostream& operator<<(std::ostream&, const Order&);
```
Example:
```c++
std::cout << order;
```
Without `friend`, private members would be inaccessible.

## 11. Operator Overloading
**Allows custom behavior for operators.**

Example:
```c++
operator<<
```
So this works:
```c++
std::cout << order;
```
Instead of:
```c++
order.print()
```
Many C++ libraries use heavy operator overloading.

## 12. Static vs Instance Members
Example:
```
Order object
-------------
id
price
```
Shared memory:
```
Order class
-------------
orderCount
```
**Every object sees the same `orderCount`.**

## 13. Example Usage
```c++
int main() {
    Order o1(1, 100);
    Order o2(2, 200);

    std::cout << o1 << std::endl;

    std::cout << Order::getOrderCount() << std::endl;
}
```
Output:
```
Order(1, 100)
2
```
## 14. Major Features of C++ Classes
A modern C++ class can include:
| Feature              | Purpose                    |
| -------------------- | -------------------------- |
| data members         | store state                |
| constructors         | initialize                 |
| destructor           | cleanup                    |
| copy constructor     | duplicate object           |
| move constructor     | transfer resources         |
| assignment operators | reassign objects           |
| member functions     | behavior                   |
| static members       | shared data                |
| friend functions     | controlled external access |
| operator overloads   | custom operators           |
| inheritance          | code reuse                 |
| virtual functions    | runtime polymorphism       |
| templates            | generic classes            |

## 15. Visual Class Model
```
class
 ├── data members
 ├── constructors
 ├── destructor
 ├── copy/move operations
 ├── member functions
 ├── static members
 ├── friend functions
 ├── operators
 └── inheritance/polymorphism
```

## 16. Real Industry Example
Example trading system class:
```
Order
 ├── id
 ├── price
 ├── quantity
 ├── timestamp
 ├── constructor
 ├── move semantics
 ├── print/debug
 └── comparison operators
```
These classes are used millions of times per second in trading engines.

So design must emphasize:
```
performance
memory ownership
cache locality
move semantics
```

## 17. Key Insight
Modern C++ classes combine:
```
OOP
RAII
move semantics
templates
```