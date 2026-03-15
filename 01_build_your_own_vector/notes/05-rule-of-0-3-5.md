This topic is extremely important for writing correct C++ classes, especially managing resources (memory, file handles, sockets, etc.).

We will go through:
- Rule of 3 (historical C++)
- Rule of 5 (modern C++)
- Rule of 0 (best modern practice)

## 1. The Problem These Rules Solve
Suppose we write a class that manages memory:
```c++
class Buffer {
private:
    int* data;

public:
    Buffer(int value) {
        data = new int(value);
    }

    ~Buffer() {
        delete data;
    }
};
```
Looks fine. But now someone writes:
```c++
Buffer a(10);
Buffer b = a;
```
What happens?   
Memory layout:
```c++
a.data → memory(10)
b.data → memory(10)
```
**Both objects point to the same memory.**   

When destructors run:
```
delete memory
delete memory again
```
Result:
```
double free → crash
```
So when a class **manages a resource**, we must control **copying behavior**.   
That is where the rules come from.

## 2. Rule of 3 (Classic C++)
The **Rule of 3** says:   
If a class defines one of these functions, it likely **needs all three**:
| Function                 | Purpose          |
| ------------------------ | ---------------- |
| Destructor               | release resource |
| Copy constructor         | copy resource    |
| Copy assignment operator | assign resource  |

Example
```c++
class Buffer {
private:
    int* data;

public:
    Buffer(int value) {
        data = new int(value);
    }

    ~Buffer() {
        delete data;
    }

    Buffer(const Buffer& other) {
        data = new int(*other.data);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
};
```
Now:
```c++
Buffer a(10);
Buffer b = a;
```
Memory:
```
a.data → memory(10)
b.data → new memory(10)
```
Safe.

## 3. Why Rule of 3 Exists

Because the compiler **automatically generates default versions**.

Default copy constructor:
```
copy pointer value
```
Not:
```
copy pointed memory
```
This is called **shallow copy**. But we need **deep copy**.

## 4. Rule of 5 (Modern C++)

C++11 introduced **move semantics** (read more in [02-move-semantics.md](./02-move-semantics.md)).

So now there are **two more special functions**.
| Function         | Purpose           |
| ---------------- | ----------------- |
| Destructor       | cleanup           |
| Copy constructor | copy resource     |
| Copy assignment  | copy resource     |
| Move constructor | transfer resource |
| Move assignment  | transfer resource |


So the **Rule of 3** becomes **Rule of 5**.

Example
```c++
class Buffer {
private:
    int* data;

public:
    Buffer(int value) {
        data = new int(value);
    }

    ~Buffer() {
        delete data;
    }

    Buffer(const Buffer& other) {
        data = new int(*other.data);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    Buffer(Buffer&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```
Move operation:
```
Buffer b = std::move(a)
```
Memory transfer:
```
a.data → nullptr
b.data → original memory
```
No expensive copying.

## 5. Rule of 0 (Best Modern Practice)
The **Rule of 0** says:
```
Do not manage resources manually.
Let existing classes manage them.
```
Example:

Instead of writing:
```
class Buffer {
    int* data;
};
```
Use:
```c++
class Buffer {
    std::unique_ptr<int> data;
};
```
Now you **don't write any of the five functions**.

Example:
```c++
class Buffer {
private:
    std::unique_ptr<int> data;

public:
    Buffer(int value)
        : data(std::make_unique<int>(value)) {}
};
```
That's it.

The compiler handles:
```
destructor
move
copy restrictions
```
This is the **Rule of 0**.

## 6. Visual Comparison
**Rule of 3**
```
Destructor
Copy constructor
Copy assignment
```
Needed for resource-owning classes.

**Rule of 5**
```
Destructor
Copy constructor
Copy assignment
Move constructor
Move assignment
```
Needed for modern C++ performance.

**Rule of 0**
```
Use RAII classes
Write none of the above
```
Best design.

## 7. Real Modern C++ Example
```c++
class Order {
private:
    std::string symbol;
    std::vector<int> trades;

public:
    Order(std::string s) : symbol(std::move(s)) {}
};
```
No destructor.   
No copy constructor.   
No move constructor.   
Because:
```
string and vector already follow RAII
```
So the compiler-generated ones are correct.

## 8. Practical Industry Guideline
Modern C++ recommendation:
```
Prefer Rule of 0
```
**Only implement Rule of 5 when writing low-level resource classes**, such as:
```
custom memory allocators
lock wrappers
file handlers
network sockets
```

## 9. One Key Insight
These rules exist because C++ objects control **resource ownership**.   
So class design must answer:
```
Who owns the resource?
How is it copied?
How is it moved?
When is it destroyed?
```
