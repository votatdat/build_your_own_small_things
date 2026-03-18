#include "../include/int_vector.hpp"
#include "test_utils.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

void test_default_constructor() {
    IntVector v;

    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v.empty());
}

void test_push_back_and_indexing() {
    IntVector v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.size() == 3);
    assert(!v.empty());

    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_capacity_growth() {
    IntVector v;

    assert(v.capacity() == 0);

    v.push_back(1);
    assert(v.capacity() == 1);

    v.push_back(2);
    assert(v.capacity() == 2);

    v.push_back(3);
    assert(v.capacity() == 4);

    v.push_back(4);
    assert(v.capacity() == 4);

    v.push_back(5);
    assert(v.capacity() == 8);
}

void test_values_preserved_after_reallocation() {
    IntVector v;

    for (int i = 0; i < 100; ++i) {
        v.push_back(i * 10);
    }

    assert(v.size() == 100);

    for (int i = 0; i < 100; ++i) {
        assert(v[static_cast<std::size_t>(i)] == i * 10);
    }
}

void test_reserve() {
    IntVector v;

    v.reserve(16);
    assert(v.capacity() >= 16);
    assert(v.size() == 0);

    v.push_back(1);
    v.push_back(2);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v.capacity() >= 16);
}

void test_reserve_does_not_shrink() {
    IntVector v;

    v.reserve(16);
    const std::size_t old_capacity = v.capacity();

    v.reserve(4);
    assert(v.capacity() == old_capacity);
}

void test_at() {
    IntVector v;
    v.push_back(11);
    v.push_back(22);

    assert(v.at(0) == 11);
    assert(v.at(1) == 22);

    bool thrown = false;
    try {
        (void)v.at(2);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

void test_front_and_back() {
    IntVector v;
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);

    assert(v.front() == 7);
    assert(v.back() == 9);

    v.front() = 70;
    v.back() = 90;

    assert(v[0] == 70);
    assert(v[2] == 90);
}

void test_pop_back() {
    IntVector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    assert(v.size() == 2);
    assert(v.back() == 2);

    v.pop_back();
    assert(v.size() == 1);
    assert(v.back() == 1);
}

void test_clear() {
    IntVector v;
    v.reserve(10);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    const std::size_t old_capacity = v.capacity();

    v.clear();

    assert(v.size() == 0);
    assert(v.empty());
    assert(v.capacity() == old_capacity);
}

void test_resize_grow_and_shrink() {
    IntVector v;

    v.resize(5, 42);
    assert(v.size() == 5);

    for (std::size_t i = 0; i < v.size(); ++i) {
        assert(v[i] == 42);
    }

    v.resize(2);
    assert(v.size() == 2);
    assert(v[0] == 42);
    assert(v[1] == 42);

    v.resize(4, 99);
    assert(v.size() == 4);
    assert(v[0] == 42);
    assert(v[1] == 42);
    assert(v[2] == 99);
    assert(v[3] == 99);
}

void test_copy_constructor() {
    IntVector original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    IntVector copy = original;

    assert(copy.size() == original.size());
    assert(copy.capacity() == original.capacity());

    for (std::size_t i = 0; i < original.size(); ++i) {
        assert(copy[i] == original[i]);
    }

    copy[0] = 100;
    assert(original[0] == 1);
    assert(copy[0] == 100);
}

void test_copy_assignment() {
    IntVector a;
    a.push_back(10);
    a.push_back(20);

    IntVector b;
    b.push_back(1);

    b = a;

    assert(b.size() == a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        assert(b[i] == a[i]);
    }

    b[1] = 999;
    assert(a[1] == 20);
    assert(b[1] == 999);
}

void test_self_copy_assignment() {
    IntVector v;
    v.push_back(5);
    v.push_back(6);

    v = v;

    assert(v.size() == 2);
    assert(v[0] == 5);
    assert(v[1] == 6);
}

void test_move_constructor() {
    IntVector original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    IntVector moved = std::move(original);

    assert(moved.size() == 3);
    assert(moved[0] == 1);
    assert(moved[1] == 2);
    assert(moved[2] == 3);

    assert(original.size() == 0);
    assert(original.capacity() == 0);
    assert(original.empty());
}

void test_move_assignment() {
    IntVector source;
    source.push_back(11);
    source.push_back(22);

    IntVector target;
    target.push_back(99);

    target = std::move(source);

    assert(target.size() == 2);
    assert(target[0] == 11);
    assert(target[1] == 22);

    assert(source.size() == 0);
    assert(source.capacity() == 0);
    assert(source.empty());
}

void test_iteration() {
    IntVector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    int sum = 0;
    for (int value : v) {
        sum += value;
    }

    assert(sum == 10);
}

void test_copy_move_tracker_smoke_test() {
    CopyMoveTracker::reset();

    {
        CopyMoveTracker a;
        CopyMoveTracker b(42);
        CopyMoveTracker c = b;
        CopyMoveTracker d = std::move(c);

        a = b;
        a = std::move(d);
    }

    assert(CopyMoveTracker::default_constructor_count == 1);
    assert(CopyMoveTracker::value_constructor_count == 1);
    assert(CopyMoveTracker::copy_constructor_count == 1);
    assert(CopyMoveTracker::move_constructor_count == 1);
    assert(CopyMoveTracker::copy_assignment_count == 1);
    assert(CopyMoveTracker::move_assignment_count == 1);
    assert(CopyMoveTracker::destructor_count == 4);
}

void test_insert_empty() {
    IntVector v;

    v.insert(0, 10);

    assert(v.size() == 1);
    assert(v[0] == 10);
}

void test_insert_front() {
    IntVector v;
    v.push_back(20);
    v.push_back(30);

    v.insert(0, 10);

    assert(v.size() == 3);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_insert_middle() {
    IntVector v;
    v.push_back(10);
    v.push_back(30);

    v.insert(1, 20);

    assert(v.size() == 3);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_insert_end() {
    IntVector v;
    v.push_back(10);
    v.push_back(20);

    v.insert(v.size(), 30);

    assert(v.size() == 3);
    assert(v[2] == 30);
}

void test_insert_reallocate() {
    IntVector v;

    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    v.insert(5, 999);

    assert(v.size() == 11);
    assert(v[5] == 999);
    assert(v[6] == 5); // shifted
}

void test_insert_invalid() {
    IntVector v;
    v.push_back(1);

    bool thrown = false;

    try {
        v.insert(2, 10);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

void test_erase_middle() {
    IntVector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.erase(1);

    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 30);
}

void test_erase_front() {
    IntVector v;
    v.push_back(10);
    v.push_back(20);

    v.erase(0);

    assert(v.size() == 1);
    assert(v[0] == 20);
}

void test_erase_last() {
    IntVector v;
    v.push_back(10);
    v.push_back(20);

    v.erase(1);

    assert(v.size() == 1);
    assert(v[0] == 10);
}

void test_erase_single() {
    IntVector v;
    v.push_back(42);

    v.erase(0);

    assert(v.size() == 0);
    assert(v.empty());
}

void test_erase_invalid() {
    IntVector v;
    v.push_back(1);

    bool thrown = false;

    try {
        v.erase(1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

int main() {
    test_default_constructor();
    test_push_back_and_indexing();
    test_capacity_growth();
    test_values_preserved_after_reallocation();
    test_reserve();
    test_reserve_does_not_shrink();
    test_at();
    test_front_and_back();
    test_pop_back();
    test_clear();
    test_resize_grow_and_shrink();
    test_copy_constructor();
    test_copy_assignment();
    test_self_copy_assignment();
    test_move_constructor();
    test_move_assignment();
    test_iteration();
    test_copy_move_tracker_smoke_test();
    test_insert_empty();
    test_insert_front();
    test_insert_middle();
    test_insert_end();
    test_insert_reallocate();
    test_insert_invalid();

    test_erase_middle();
    test_erase_front();
    test_erase_last();
    test_erase_single();
    test_erase_invalid();

    std::cout
        << "All IntVector tests passed.\n";
    return 0;
}