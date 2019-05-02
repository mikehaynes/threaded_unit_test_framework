#include "assert_funcs.h"

using namespace std;

void assert_almost_equal(const double d1, const double d2, const double prec,
                         const int line, const string& test_name) {
    double result = d1 - d2;
    result = (result < 0.0) ? result * -1 : result;
    if (result > prec) {
        TestRig::get()->add_failure(test_name, TestFailure(NOT_ALMOST_EQUAL, line));
    }
}

void assert_true(const bool cond, const int line, const string& test_name) {
    if (!cond) {
        TestRig::get()->add_failure(test_name, TestFailure(FALSE, line));
    }
}

void assert_false(const bool cond, const int line, const string& test_name) {
    if (cond) {
        TestRig::get()->add_failure(test_name, TestFailure(TRUE, line));
    }
}