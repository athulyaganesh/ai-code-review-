// Tiny test helper (no external test framework needed).
#ifndef SCALE_TEST_CHECK_H
#define SCALE_TEST_CHECK_H

#include <cstdio>
#include <string>

static int g_failures = 0;

#define CHECK_EQ(actual, expected)                                              \
    do {                                                                        \
        long long a_ = (long long)(actual), e_ = (long long)(expected);         \
        if (a_ != e_) {                                                         \
            std::printf("FAIL %s:%d  %s == %lld, expected %lld\n",              \
                        __FILE__, __LINE__, #actual, a_, e_);                   \
            g_failures++;                                                       \
        }                                                                       \
    } while (0)

#define CHECK_STR(actual, expected)                                             \
    do {                                                                        \
        std::string a_ = (actual), e_ = (expected);                             \
        if (a_ != e_) {                                                         \
            std::printf("FAIL %s:%d  %s == \"%s\", expected \"%s\"\n",          \
                        __FILE__, __LINE__, #actual, a_.c_str(), e_.c_str());   \
            g_failures++;                                                       \
        }                                                                       \
    } while (0)

#define TEST_MAIN_END()                                                         \
    do {                                                                        \
        if (g_failures == 0) std::printf("all checks passed\n");                \
        return g_failures == 0 ? 0 : 1;                                         \
    } while (0)

#endif
