#ifndef MACROS_H
#define MACROS_H

#include <string>

#include "assert_funcs.h"
#include "TestRig.h"

#define TEST(name)                                                            \
    static void name(const std::string&);                                     \
    static TestRegisterer reg_##name((#name), name);                          \
    static void name(const std::string& name_str = (#name))

#define MAIN()                                                                \
    int main() {                                                              \
        TestRig::get()->run_tests();                                          \
        return 0;                                                             \
    }

#define ASSERT_EQUAL(first, second)                                           \
    assert_equal((first), (second), __LINE__, (name_str))

#define ASSERT_NOT_EQUAL(first, second)                                       \
    assert_not_equal((first), (second), __LINE__, (name_str))

#define ASSERT_ALMOST_EQUAL(first, second, precision)                         \
    assert_almost_equal((first), (second), (precision), __LINE__, (name_str))

#define ASSERT_TRUE(value)                                                    \
    assert_true((value), __LINE__, (name_str))

#define ASSERT_FALSE(value)                                                   \
    assert_false((value), __LINE__, (name_str))

struct Lock {
    static void print_lock();
    static void print_unlock();
    static void resource_lock();
    static void resource_unlock();
};

#endif // !MACROS_H
