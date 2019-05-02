#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <vector>

#include "threadunit.h"

using namespace std;

TEST(long_test2) {
    const int SIZE = 1000000;
    srand(time(nullptr));
    vector<int> vals;
    
    for (int i = 0; i < SIZE; ++i) {
        vals.push_back(rand());
    }

    sort(vals.begin(), vals.end());

    int prev = vals[0];
    for (int i = 1; i < SIZE; ++i) {
        ASSERT_TRUE(prev <= vals[i]);
        prev = vals[i];
    }
}

TEST(long_test3) {
    const int SIZE = 5000000;
    srand(time(nullptr));
    vector<int> vals;

    for (int i = 0; i < SIZE; ++i) {
        vals.push_back(rand());
    }

    sort(vals.begin(), vals.end());

    int prev = vals[0];
    for (int i = 1; i < SIZE; ++i) {
        ASSERT_TRUE(prev <= vals[i]);
        prev = vals[i];
    }
}

TEST(long_test4) {
    const int SIZE = 10000000;
    srand(time(nullptr));
    vector<int> vals;
    vals.reserve(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        vals.push_back(rand());
    }

    sort(vals.begin(), vals.end());

    int& prev = vals[0];
    for (int i = 1; i < SIZE; ++i) {
        ASSERT_TRUE(prev <= vals[i]);
        prev = vals[i];
    }
}

TEST(long_test5) {
    const int SIZE = 20000000;
    srand(time(nullptr));
    vector<int> vals;
    vals.reserve(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        vals.push_back(rand());
    }

    sort(vals.begin(), vals.end());

    int& prev = vals[0];
    for (int i = 1; i < SIZE; ++i) {
        ASSERT_TRUE(prev <= vals[i]);
        prev = vals[i];
    }
}

TEST(fail_test) {
    ASSERT_EQUAL(1, 2);
    ASSERT_NOT_EQUAL(1, 1);
    ASSERT_ALMOST_EQUAL(0.0, 0.1, 0.01);
    ASSERT_TRUE(false);
    ASSERT_FALSE(true);
}

TEST(simple_test) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

TEST(long_test1) {
    bool go = true;
    int val = 0;

    while (go) {
        if (val % 2 == 0) {
            val += 3;
        }
        else {
            val -= 1;
        }
        if (val > 2000000000) {
            go = false;
        }
    }
}

TEST(random_test) {
    srand(time(nullptr));
    int vals[10];

    for (int i = 0; i < 10; ++i) {
        vals[i] = rand() % 10;
    }

    ASSERT_NOT_EQUAL(vals[0], vals[1]);
    ASSERT_NOT_EQUAL(vals[1], vals[2]);
    ASSERT_NOT_EQUAL(vals[2], vals[3]);
    ASSERT_NOT_EQUAL(vals[3], vals[4]);
    ASSERT_NOT_EQUAL(vals[4], vals[5]);
    ASSERT_NOT_EQUAL(vals[5], vals[6]);
    ASSERT_NOT_EQUAL(vals[6], vals[7]);
    ASSERT_NOT_EQUAL(vals[7], vals[8]);
    ASSERT_NOT_EQUAL(vals[8], vals[9]);
}

MAIN()