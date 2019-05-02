#ifndef THREADUNIT_H
#define THREADUNIT_H

/* --- USAGE ---


In a single source code file, add a series of test blocks followed by
a main block, like the following example:

    --- example.cpp ---

    #include "threadunit.h"

    TEST(test_name1) {
        ...
    }

    TEST(test_name2) {
        ...
    }

    ...

    TEST(test_nameN) {
        ...
    }

    MAIN()

    --- !example.cpp ---

When run, the library infrustructure will assign each test block to a
thread and run it.  This is useful when you have a large number of lengthy
unit tests you need to run.  It is recommended that each test block only
tests a small part of functionality, since this will make your tests more
informative to you.

Each test name must be unique.  The infrastructure uses the name as an
identifier for each test.  Naming two tests the same name will cause undefined
behavior.

Since the library is threaded, I recommend not using shared resources between
any tests and not printing to standard out.  In the event you feel this is
necessary, two locks used by the infrastructure are available for you to use, a
print lock and a resource lock.  You can find how to use them in the INTERFACE
section of this file.

Printing to standard out can mess up the format of the infrastructure's output.
I recommend using strings or string streams along with the provided assert
functions to compare outputs, or printing your output to a file using file
streams.

The infrastructure requires you to use its assert functions to catch errors.
These include ASSERT_TRUE(), ASSERT_FALSE(), ASSERT_EQUAL(), ASSERT_NOT_EQUAL(),
and ASSERT_ALMOST_EQUAL().  Details on each one are provided in the INTERFACE
section of this file.


   --- !USAGE --- */


/* --- INTERFACE ---


    --- TEST BLOCK ---

    Test blocks take the following form:

        TEST(test_name) {
            // Insert test code here
        }

    Every test name should be a unique string with no white space.  Do not
    put the test name in quotation marks (" "), the infrastructure will convert
    the string as needed.  I recommend giving your tests informative names that
    make them easy to indentify in the test results.  Assert statements are
    required to properly use the testing infrastructure.  They are explained
    later in this section.

    --- !TEST BLOCK ---

    --- MAIN ---

    The test main function takes the following form:

        MAIN()

    You should not follow it with a semicolon and it should be placed at the
    very end of your test file.  This function is required for your tests to
    compile and run.

    --- !MAIN ---

    --- ASSERT TRUE ---

    This assert function takes the following form:

        ASSERT_TRUE(const bool condition);

    This function must be used inside of a test block. It checks if the
    condition parameter is true.  If it is not, an error message with a line
    number is printed by the infrastructure and tests resume.

    --- !ASSERT TRUE ---

    --- ASSERT FALSE ---

    This assert function takes the following form:

        ASSERT_FALSE(const bool condition);

    This function must be used inside of a test block.  It checks if the
    condition parameter is false.  If it is not, an error message with a line
    number is printed by the infrastructure and tests resume.

    --- !ASSERT FALSE ---

    --- ASSERT EQUAL ---

    This assert function takes the following form:

        ASSERT_EQUAL(const T& value1, const T& value2);

    This is a templated function.  The parameters need to be of the same type
    or implicitly castable to the same type.  The parameters also need to
    support the equality operator (==).  This function must be used inside of
    a test block.  It checks if the parameters are equal using the equality
    operator (==).  If they are not equal, an error message with a line number
    is printed by the infrastructure and tests resume.

    --- !ASSERT EQUAL ---

    --- ASSERT NOT EQUAL ---

    This assert functin takes the following form:

        ASSERT_NOT_EQUAL(const T& value1, const T& value2);

    This is a templated function.  The parameters need to be of the same type
    or implicitly castable to the same type.  The parameters also need to
    support the not equal operator (!=).  This function must be used inside of
    a test block.  It checks if the parameters are different using the not
    equal operator (!=).  If they are equal, an error message with a line
    number is printed by the infrastructure and tests resume.

    --- !ASSERT NOT EQUAL ---

    --- ASSERT ALMOST EQUAL ---

    This assert function takes the following form:

        ASSERT_ALMOST_EQUAL(const double value1, const double value2, const double precision);

    This function must be used inside of a test block.  It should be used for
    floating point comparisons.  It checks if the parameters are equal within
    a certain level of precision in a way similar to the following:

        | value1 - value2 | <= precision

    The precision parameter should be a positive value.  If the above equation
    is false, an error message with a line number is printed by the
    infrastructure and tests resume.

    --- !ASSERT ALMOST EQUAL ---

    --- PRINT LOCK ---

    This functionality takes the following form:

        Lock::print_lock();
        Lock::print_unlock();

    These functions allow you to print to standard out deterministically, so
    that your output does not become garbled and unreadable.  The lock function
    must be followed by the unlock function, or else the infrastructure will
    fail to complete execution properly.  These functions are static members
    the Lock class used by the infrastructure.

    It is highly recommended that you do not print to standard out while doing
    unit testing, but if you choose to do so, you must use the print lock
    to do so.  Use the print lock as follows:

        Lock::print_lock();
        cout << "Hello world." << endl;
        Lock::print_unlock();

    --- !PRINT LOCK ---

    --- RESOURCE LOCK ---

    This functionality takes the following form:

        Lock::resource_lock();
        Lock::resource_unlock();

    These functions allow you to safely use resources shared by two or more
    test blocks.  The lock function must be followed by the unlock function,
    or else the infrastructure may fail to complete execution properly.  These
    functions are static members of the Lock class used by the infrastructure.

    It is recommended that you do not use shared resources between test blocks,
    but if you must, you should use the resource lock to do so.  Use the
    resource lock as follows:

        std::vector<int> values;

        TEST(test1) {
            Lock::resource_lock();
            values.push_back(5);
            Lock::resource_unlock();
        }

        TEST(test2) {
            Lock::resource_lock();
            values.push_back(3);
            Lock::resource_unlock();
        }

    --- !RESOURCE LOCK ---


   --- !INTERFACE --- */

#endif // !THREADUNIT_H

#include "macros.h"