#include <iostream>

#include "TestRig.h"

using namespace std;

mutex TestRig::print_lock_;
mutex TestRig::resource_lock_;
TestRig* TestRig::instance = TestRig::get();

TestRig::TestRig() {
    fails = 0;
}

TestRig* TestRig::get() {
    if (not instance) {
        instance = new TestRig;
    }

    return instance;
}

void TestRig::add_test(const string& name, test_func_t func) {
    tests[name] = test_t(name, func);
}

void TestRig::add_failure(const string& name, const TestFailure& fail) {
    tests[name].fails.push_back(fail);
}

void TestRig::run_tests() {
    size_t size = tests.size();
    vector<thread*> threads(size, nullptr);

    size_t k = 0;
    for (auto iter = tests.begin(); iter != tests.end(); ++k, ++iter) {
        threads[k] = new thread(test_helper, iter->first);
    }

    for (size_t i = 0; i < size; ++i) {
        threads[i]->join();
        delete threads[i];
        threads[i] = nullptr;
    }

    print_lock_.lock();
    cout << "\nTesting Complete!" << endl
         << "Failures: " << fails << endl
         << "Successes: " << tests.size() - fails << endl
         << "Total tests: " << tests.size() << endl;
    print_lock_.unlock();
}

void TestRig::test_helper(const string name) {
    stringstream ss;
    bool failure = false;

    test_t& test = TestRig::get()->tests[name];

    TestRig::get()->print_line(ss);
    TestRig::get()->print_test_header(ss, test);

    test.func(test.name);
    failure = TestRig::get()->print_test_results(ss, test);

    if (failure) {
        resource_lock_.lock();
        TestRig::get()->fails++;
        resource_lock_.unlock();
    }

    TestRig::get()->print_test_footer(ss, failure);
    TestRig::get()->print_line(ss);

    print_lock_.lock();
    cout << ss.str();
    print_lock_.unlock();
}

bool TestRig::print_test_results(stringstream& ss, const test_t& test) {
    if (test.fails.empty()) {
        return false;
    }

    for (size_t i = 0; i < test.fails.size(); ++i) {
        ss << "At line " << test.fails[i].get_line() << ": "
           << test.fails[i].get_message() << endl;
    }

    return true;
}

void TestRig::print_test_footer(stringstream& ss, const bool failure) {
    if (failure) {
        ss << "\nTest Failed!" << endl;
    }
    else {
        ss << "Test Successful!" << endl;
    }
}

void TestRig::print_test_header(stringstream& ss, const test_t& test) {
    ss << "Running test: " << test.name << endl << endl;
}

void TestRig::print_line(stringstream& ss) {
    for (int i = 0; i < 80; ++i) {
        ss << '-';
    }
    ss << endl;
}

void TestRig::print_lock() {
    print_lock_.lock();
}

void TestRig::print_unlock() {
    print_lock_.unlock();
}

void TestRig::res_lock() {
    resource_lock_.lock();
}

void TestRig::res_unlock() {
    resource_lock_.unlock();
}

const string EQUAL_STR = "Expected values to be not equal, but they were equal";
const string NOT_EQUAL_STR = "Expected values to be equal, but they were not equal";
const string NOT_ALMOST_EQUAL_STR = "Expected values to be almost equal, but they were too different";
const string TRUE_STR = "Expected value to be false, but it was true";
const string FALSE_STR = "Expected value to be true, but it was false";

TestFailure::TestFailure(const ErrorMessageID id, const int line_num) {
    error_id = id;
    line = line_num;
}

const string& TestFailure::get_message() const {
    switch (error_id) {
    case EQUAL:
        return EQUAL_STR;
        break;
    case NOT_EQUAL:
        return NOT_EQUAL_STR;
        break;
    case FALSE:
        return FALSE_STR;
        break;
    case TRUE:
        return TRUE_STR;
        break;
    default:
        return NOT_ALMOST_EQUAL_STR;
        break;
    }
}

const int TestFailure::get_line() const {
    return line;
}

TestRegisterer::TestRegisterer(const string& name, test_func_t func) {
    TestRig::get()->add_test(name, func);
}

test_t::test_t() {
    name = "";
}

test_t::test_t(const string& test_name, test_func_t function) {
    name = test_name;
    func = function;
}