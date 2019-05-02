#ifndef TESTRIG_H
#define TESTRIG_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <thread>
#include <sstream>

using test_func_t = void(*)(const std::string&);

enum ErrorMessageID { EQUAL, NOT_EQUAL, FALSE, TRUE, NOT_ALMOST_EQUAL };

class TestFailure {
public:
    TestFailure(const ErrorMessageID, const int);

    const std::string& get_message() const;
    const int get_line() const;

private:
    ErrorMessageID error_id;
    int line;
};

struct test_t {
    test_t();
    test_t(const std::string&, test_func_t);
    std::string name;
    test_func_t func;
    std::vector<TestFailure> fails;
};

class TestRig {
public:
    TestRig();

    static TestRig* get();

    void add_test(const std::string&, test_func_t);
    void run_tests();

    void add_failure(const std::string&, const TestFailure&);
    
    static void print_lock();
    static void print_unlock();

    static void res_lock();
    static void res_unlock();

private:
    int fails;

    static TestRig* instance;

    static std::mutex print_lock_;
    static std::mutex resource_lock_;

    std::map<std::string, test_t> tests;

    static void test_helper(const std::string);

    void print_line(std::stringstream&);
    void print_test_header(std::stringstream&, const test_t&);
    void print_test_footer(std::stringstream&, const bool);
    bool print_test_results(std::stringstream&, const test_t&);
};

struct TestRegisterer {
    TestRegisterer(const std::string&, test_func_t);
};

#endif // !TESTRIG_H