## 1. Basic Structure of a C++ Class
A minimal class:
```c++
class Animal {
private:
    int age;

public:
    Animal(int a) : age(a) {}

    void speak() {
        std::cout << "Animal sound\n";
    }
};
```
| Section     | Purpose                          |
| ----------- | -------------------------------- |
| `private`   | accessible only inside the class |
| `public`    | accessible outside               |
| constructor | initializes object               |
| methods     | behavior                         |
| destructor  | cleanup                          |

## 2. Special Member Functions
C++ automatically generates some functions for classes.
| Function            | Purpose               |
| ------------------- | --------------------- |
| Default constructor | `A()`                 |
| Destructor          | `~A()`                |
| Copy constructor    | `A(const A&)`         |
| Copy assignment     | `operator=(const A&)` |
| Move constructor    | `A(A&&)`              |
| Move assignment     | `operator=(A&&)`      |
Example:
```c++
class A {
public:
    A();
    ~A();
    A(const A&);
    A& operator=(const A&);
    A(A&&);
    A& operator=(A&&);
};
```
## 3. Some weird syntax (weird to me)
### `= 0` (Pure Virtual Functions)
```c++
class Shape {
public:
    virtual double area() = 0;
};
```
**area() must be implemented in derived classes** => this makes class `abstract`

### `= default`
```c++
class A {
public:
    A() = default;
};
```
**use compiler-generated implementation**   
Normally the compiler generates default functions automatically, but sometimes you must explicitly request them.

### `= delete`
```c++
class A {
public:
    A(const A&) = delete;
};
```
**copy constructor is forbidden**   
```c++
A a;
A b = a;  // compile error
```

## 4. Examples
```c++
#include <iostream>

class Base {
public:
    Base() = default;

    virtual void speak() = 0;

    Base(const Base&) = delete;
};

class Dog : public Base {
public:
    void speak() override {
        std::cout << "Woof\n";
    }
};
```
Usage:
```c++
Dog d;
d.speak();
```
Rules enforced:
```
Base cannot be instantiated
Base cannot be copied
Dog must implement speak()
```