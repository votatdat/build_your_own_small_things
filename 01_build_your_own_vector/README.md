# Build Your Own Vector in C++

A progressive reimplementation of a `std::vector`-like container in modern C++.

This project focuses on **understanding container internals**, **memory management**, and **performance tradeoffs**, which are essential skills for **systems programming and quantitative development**.

Rather than simply using `std::vector`, this project rebuilds a vector step-by-step to explore how dynamic arrays work internally.

---

# Motivation

C++ developers often rely heavily on `std::vector`, but few fully understand how it works internally.

Understanding vector implementation teaches important systems programming concepts:

* dynamic memory management
* contiguous storage
* amortized complexity
* copy vs move semantics
* iterator invalidation
* exception safety
* object lifetime management

---

# Project Goals

The goals of this project are:

1. Understand how dynamic arrays grow.
2. Learn how C++ manages object lifetime.
3. Implement copy and move semantics correctly.
4. Explore memory allocation and construction separately.
5. Understand iterator behavior and invalidation.
6. Build a container with predictable performance characteristics.

---

# Features

Implemented progressively through milestones.

## Core Container

* dynamic contiguous storage
* `size()` and `capacity()`
* amortized `O(1)` append
* automatic growth strategy

## Element Access

* `operator[]`
* `at()`
* `front()`
* `back()`

## Modifiers

* `push_back`
* `pop_back`
* `clear`
* `reserve`
* `resize`

## Iterators

* `begin()`
* `end()`

## Modern C++ Support

* Rule of Five
* move semantics
* perfect forwarding
* `emplace_back`

## Memory Control

* manual object construction
* manual destruction
* raw memory allocation

---

# Project Structure

```
build-your-own-vector/
│
├── CMakeLists.txt
├── README.md
│
├── include/
│   ├── int_vector.hpp
│   └── vector.hpp
│
├── src/
│   ├── int_vector.cpp
│   └── main.cpp
│
├── tests/
│   ├── test_int_vector.cpp
│   ├── test_vector.cpp
│   └── test_utils.hpp
│
├── examples/
│   ├── demo_int_vector.cpp
│   └── demo_vector.cpp
│
└── notes/
    ├── 01-[...].md
    ├── 02-[...].md
    ├── 03-[...].md
    ├── 04-[...].md
    └── 05-[...].md
```

---

# Milestone Roadmap

The container is built progressively through several milestones.

---

## Milestone 1 — IntVector

Implement a vector that only stores integers.

Features:

* constructor
* destructor
* `push_back`
* `size`
* `capacity`
* `reserve`
* `operator[]`

Concepts learned:

* heap allocation
* contiguous storage
* growth strategy

---

## Milestone 2 — Safe Access & Modifiers

Add basic container functionality.

Features:

* `at`
* `front`
* `back`
* `pop_back`
* `clear`

Concepts learned:

* bounds checking
* logical deletion vs memory deallocation

---

## Milestone 3 — Rule of Three

Add proper copy semantics.

Features:

* copy constructor
* copy assignment
* destructor

Concepts learned:

* resource ownership
* shallow vs deep copy
* self-assignment protection

---

## Milestone 4 — Rule of Five

Add move semantics.

Features:

* move constructor
* move assignment

Concepts learned:

* move semantics
* ownership transfer
* performance benefits of moves

---

## Milestone 5 — Template Vector

Generalize the container to support any type.

```
template<typename T>
class Vector;
```

Concepts learned:

* templates
* generic programming
* type-dependent behavior

---

## Milestone 6 — Perfect Forwarding

Improve insertion performance.

Features:

* `push_back(const T&)`
* `push_back(T&&)`
* `emplace_back(...)`

Concepts learned:

* lvalue vs rvalue
* perfect forwarding
* avoiding unnecessary copies

---

## Milestone 7 — Iterators

Support standard iteration patterns.

Features:

* `begin()`
* `end()`

Concepts learned:

* pointer-based iterators
* range-based loops
* iterator invalidation

---

## Milestone 8 — Manual Object Lifetime

Separate allocation from construction.

Concepts learned:

* raw memory allocation
* placement new
* explicit destruction
* `std::uninitialized_move`
* `std::destroy_at`

This step moves the implementation closer to real `std::vector`.

---

## Milestone 9 — Exception Safety

Ensure robust behavior during failures.

Concepts learned:

* strong exception guarantee
* rollback during failed reallocations
* avoiding memory leaks

---

## Milestone 10 — Benchmarking

Evaluate container performance.

Experiments include:

* push_back with and without `reserve`
* copy vs move insertion
* reallocation cost
* comparison with `std::vector`

---

# Example Usage

```
Vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);

for (auto value : v)
{
    std::cout << value << std::endl;
}
```

Output:

```
10
20
30
```

---

# Build Instructions

This project uses **CMake**.

```
mkdir build
cd build

cmake ..
make
```

Run example:

```
./vector_demo
```

Run tests:

```
./vector_tests
```

---

# Tests

Tests validate:

* size and capacity behavior
* correct growth and reallocation
* copy and move semantics
* element lifetime management
* iterator correctness

The project includes helper types such as:

* `CopyMoveTracker`
* `ThrowOnCopy`
* `NonTrivialType`

These help verify container behavior.

---

# Key Design Concepts

## Size vs Capacity

```
size      = number of active elements
capacity  = allocated storage
```

Capacity grows automatically when size reaches the limit.

---

## Growth Strategy

Vector capacity typically grows geometrically:

```
1 → 2 → 4 → 8 → 16 → ...
```

This ensures `push_back` has **amortized O(1)** complexity.

---

## Iterator Invalidation

Reallocation moves elements to a new memory location.

Therefore:

* pointers
* references
* iterators

to elements become **invalid**.

---

## Contiguous Storage

Elements are stored sequentially in memory:

```
[ element ][ element ][ element ]
```

Benefits:

* CPU cache efficiency
* fast random access
* good performance in numerical workloads

---

# Quant Developer Relevance

This project directly relates to concepts used in quantitative systems.

Key lessons include:

## Memory Layout

Contiguous memory improves cache locality in numerical computations.

---

## Allocation Costs

Frequent allocations can introduce latency spikes.

Using `reserve()` can reduce reallocation overhead.

---

## Object Movement

Move semantics reduce the cost of transferring large data structures.

---

## Iterator Safety

Understanding when pointers become invalid is critical in large systems.

---

## Predictable Performance

Containers used in trading systems must behave predictably under load.

---

# Limitations

This implementation is educational and does not fully replicate `std::vector`.

Missing features include:

* allocator customization
* full STL iterator support
* advanced exception guarantees
* compatibility with all STL algorithms

---

# References

Recommended resources:

* *Effective Modern C++* — Scott Meyers
* *C++ Crash Course* — Josh Lospinoso
* *C++ Templates: The Complete Guide*
* *Design Patterns for High-Performance C++*

---

# License

MIT License

This project is for educational purposes.
