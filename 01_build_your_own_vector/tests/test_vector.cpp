#include "../include/vector.hpp"
#include "test_utils.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

// Custom tracked type for move/copy semantics testing
class TrackedType {
public:
    static int live_count;
    static int copy_count;
    static int move_count;

    int value;

    TrackedType(int v = 0) : value(v) { ++live_count; }
    ~TrackedType() { --live_count; }

    TrackedType(const TrackedType& other) : value(other.value) {
        ++live_count;
        ++copy_count;
    }

    TrackedType& operator=(const TrackedType& other) {
        value = other.value;
        ++copy_count;
        return *this;
    }

    TrackedType(TrackedType&& other) noexcept : value(other.value) {
        ++live_count;
        ++move_count;
        other.value = 0;
    }

    TrackedType& operator=(TrackedType&& other) noexcept {
        value = other.value;
        ++move_count;
        other.value = 0;
        return *this;
    }

    static void reset() {
        live_count = 0;
        copy_count = 0;
        move_count = 0;
    }
};

int TrackedType::live_count = 0;
int TrackedType::copy_count = 0;
int TrackedType::move_count = 0;

void test_vector_int() {
    // A. Empty vector
    {
        Vector<int> v;
        assert(v.size() == 0);
        assert(v.capacity() == 0);
        assert(v.empty() == true);
        assert(v.begin() == v.end());
    }

    // B. One push_back
    {
        Vector<int> v;
        v.push_back(42);
        assert(v.size() == 1);
        assert(v[0] == 42);
        assert(v.front() == 42);
        assert(v.back() == 42);
    }

    // C. Many pushes (multiple reallocations)
    {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) {
            v.push_back(i);
        }
        assert(v.size() == 100);
        assert(v.capacity() >= 100);
        for (int i = 0; i < 100; ++i) {
            assert(v[i] == i);
        }
    }

    // D. Reserve
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        std::size_t old_size = v.size();
        v.reserve(50);
        assert(v.size() == old_size);
        assert(v.capacity() >= 50);
        assert(v[0] == 1);
        assert(v[1] == 2);
    }

    // E. Resize smaller
    {
        Vector<int> v;
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }
        v.resize(5);
        assert(v.size() == 5);
        for (int i = 0; i < 5; ++i) {
            assert(v[i] == i);
        }
    }

    // F. Resize larger
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.resize(5, 99);
        assert(v.size() == 5);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 99);
        assert(v[3] == 99);
        assert(v[4] == 99);
    }

    // G. Insert at beginning, middle, end
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.insert(1, 2);
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);

        v.insert(0, 0);
        assert(v[0] == 0);
        assert(v[1] == 1);

        v.insert(v.size(), 99);
        assert(v.back() == 99);
    }

    // H. Erase at beginning, middle, end
    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i) {
            v.push_back(i);
        }

        v.erase(0);
        assert(v.size() == 4);
        assert(v[0] == 1);

        v.erase(1);
        assert(v[1] == 3);

        v.erase(v.size() - 1);
        assert(v.size() == 2);
    }

    // I. Pop_back repeatedly
    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i) {
            v.push_back(i);
        }
        while (!v.empty()) {
            v.pop_back();
        }
        assert(v.size() == 0);
    }
}

void test_vector_string() {
    // A. Push string literals
    {
        Vector<std::string> v;
        v.push_back("hello");
        v.push_back("world");
        v.push_back("test");
        assert(v.size() == 3);
        assert(v[0] == "hello");
        assert(v[1] == "world");
        assert(v[2] == "test");
    }

    // B. Insert strings
    {
        Vector<std::string> v;
        v.push_back("a");
        v.push_back("c");
        v.insert(1, "b");
        assert(v[0] == "a");
        assert(v[1] == "b");
        assert(v[2] == "c");
    }

    // C. Erase strings
    {
        Vector<std::string> v;
        v.push_back("x");
        v.push_back("y");
        v.push_back("z");
        v.erase(1);
        assert(v[0] == "x");
        assert(v[1] == "z");
        assert(v.size() == 2);
    }

    // D. Copy constructor
    {
        Vector<std::string> a;
        a.push_back("one");
        a.push_back("two");
        Vector<std::string> b = a;
        b[0] = "ONE";
        assert(a[0] == "one");
        assert(b[0] == "ONE");
    }

    // E. Copy assignment
    {
        Vector<std::string> a, b;
        a.push_back("alpha");
        b.push_back("beta");
        b = a;
        b[0] = "ALPHA";
        assert(a[0] == "alpha");
        assert(b[0] == "ALPHA");
    }

    // F. Self-assignment
    {
        Vector<std::string> a;
        a.push_back("self");
        a = a;
        assert(a[0] == "self");
    }
}

void test_move_semantics() {
    // A. Move constructor
    {
        Vector<std::string> a;
        a.push_back("move");
        a.push_back("test");
        Vector<std::string> b = std::move(a);
        assert(b[0] == "move");
        assert(a.empty());
    }

    // B. Move assignment
    {
        Vector<std::string> a, b;
        a.push_back("source");
        b = std::move(a);
        assert(b[0] == "source");
        assert(a.empty());
    }

    // C. Push_back with temporary
    {
        Vector<std::string> v;
        v.push_back(std::string("temp1"));
        v.push_back(std::string("temp2"));
        assert(v[0] == "temp1");
        assert(v[1] == "temp2");
    }
}

void test_tracked_type() {
    // A. Repeated push_back with temporaries
    {
        TrackedType::reset();
        {
            Vector<TrackedType> v;
            for (int i = 0; i < 5; ++i) {
                v.push_back(TrackedType(i));
            }
            assert(v.size() == 5);
            assert(TrackedType::move_count > 0);
        }
        assert(TrackedType::live_count == 0);
    }

    // B. Reallocation with move
    {
        TrackedType::reset();
        {
            Vector<TrackedType> v;
            v.reserve(2);
            v.push_back(TrackedType(1));
            v.push_back(TrackedType(2));
            int moves_before = TrackedType::move_count;
            v.push_back(TrackedType(3));
            assert(TrackedType::move_count > moves_before);
        }
        assert(TrackedType::live_count == 0);
    }

    // C. Scope end cleanup
    {
        TrackedType::reset();
        {
            Vector<TrackedType> v;
            v.push_back(TrackedType(1));
            v.push_back(TrackedType(2));
            assert(TrackedType::live_count > 0);
        }
        assert(TrackedType::live_count == 0);
    }
}

void test_edge_cases() {
    // A. Insert into empty at position 0
    {
        Vector<int> v;
        v.insert(0, 42);
        assert(v.size() == 1);
        assert(v[0] == 42);
    }

    // B. Erase only element
    {
        Vector<int> v;
        v.push_back(1);
        v.erase(0);
        assert(v.size() == 0);
        assert(v.empty());
    }

    // C. Insert at size()
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.insert(v.size(), 3);
        assert(v.size() == 3);
        assert(v[2] == 3);
    }

    // D. Invalid insert position
    {
        Vector<int> v;
        v.push_back(1);
        try {
            v.insert(v.size() + 1, 5);
            assert(false);
        } catch (const std::out_of_range&) {}
    }

    // E. Invalid erase position
    {
        Vector<int> v;
        v.push_back(1);
        try {
            v.erase(v.size());
            assert(false);
        } catch (const std::out_of_range&) {}

        try {
            v.erase(999);
            assert(false);
        } catch (const std::out_of_range&) {}
    }

    // F. Invalid at()
    {
        Vector<int> v;
        v.push_back(1);
        try {
            v.at(v.size());
            assert(false);
        } catch (const std::out_of_range&) {}
    }

    // G. front()/back() on empty
    {
        Vector<int> v;
        try {
            v.front();
            assert(false);
        } catch (const std::out_of_range&) {}

        try {
            v.back();
            assert(false);
        } catch (const std::out_of_range&) {}
    }

    // H. Reserve smaller than size
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        std::size_t old_size = v.size();
        std::size_t old_capacity = v.capacity();
        v.reserve(1);
        assert(v.size() == old_size);
        assert(v.capacity() == old_capacity);
    }

    // I. Clear and reuse
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.clear();
        assert(v.empty());
        v.push_back(3);
        assert(v.size() == 1);
        assert(v[0] == 3);
    }
}

int main() {
    test_vector_int();
    test_vector_string();
    test_move_semantics();
    test_tracked_type();
    test_edge_cases();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
