#include "macros.h"

using namespace std;

void Lock::print_lock() {
    TestRig::print_lock();
}

void Lock::print_unlock() {
    TestRig::print_unlock();
}

void Lock::resource_lock() {
    TestRig::res_lock();
}

void Lock::resource_unlock() {
    TestRig::res_unlock();
}