#pragma once

#include <utility>

struct CopyMoveTracker {
    inline static int default_constructor_count = 0;
    inline static int value_constructor_count = 0;
    inline static int copy_constructor_count = 0;
    inline static int move_constructor_count = 0;
    inline static int copy_assignment_count = 0;
    inline static int move_assignment_count = 0;
    inline static int destructor_count = 0;

    int value = 0;

    CopyMoveTracker()
        : value(0) {
        ++default_constructor_count;
    }

    explicit CopyMoveTracker(int v)
        : value(v) {
        ++value_constructor_count;
    }

    CopyMoveTracker(const CopyMoveTracker& other)
        : value(other.value) {
        ++copy_constructor_count;
    }

    CopyMoveTracker(CopyMoveTracker&& other) noexcept
        : value(other.value) {
        other.value = -1;
        ++move_constructor_count;
    }

    CopyMoveTracker& operator=(const CopyMoveTracker& other) {
        if (this != &other) {
            value = other.value;
        }
        ++copy_assignment_count;
        return *this;
    }

    CopyMoveTracker& operator=(CopyMoveTracker&& other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = -1;
        }
        ++move_assignment_count;
        return *this;
    }

    ~CopyMoveTracker() {
        ++destructor_count;
    }

    static void reset() {
        default_constructor_count = 0;
        value_constructor_count = 0;
        copy_constructor_count = 0;
        move_constructor_count = 0;
        copy_assignment_count = 0;
        move_assignment_count = 0;
        destructor_count = 0;
    }
};