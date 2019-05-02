#ifndef ASSERT_FUNCS_H
#define ASSERT_FUNCS_H

#include <string>

#include "TestRig.h"

template <typename Type1, typename Type2>
void assert_equal(const Type1& t1, const Type2& t2, const int line,
                  const std::string& test_name) {
    if (t1 != t2) {
        TestRig::get()->add_failure(test_name, TestFailure(NOT_EQUAL, line));
    }
}

template <typename Type1, typename Type2>
void assert_not_equal(const Type1& t1, const Type2& t2, const int line,
                      const std::string& test_name) {
    if (t1 == t2) {
        TestRig::get()->add_failure(test_name, TestFailure(EQUAL, line));
    }
}

void assert_almost_equal(const double, const double, const double, const int,
                         const std::string&);

void assert_true(const bool, const int, const std::string&);

void assert_false(const bool, const int, const std::string&);


#endif // !ASSERT_FUNCS_H
