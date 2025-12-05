#include "solution.h"
#include "test.h"
#include <chrono>
#include "solution.h"
#include "test.h"
#include <cstring>
#include <chrono>
using namespace std;
using namespace std::chrono;

Solution sol;
Test test;

int main(int argc, char* argv[]) {
    #ifndef TEST_TO_RUN
    #define TEST_TO_RUN 1
    #endif

    #if TEST_TO_RUN == 1
        test.test1();
    #elif TEST_TO_RUN == 2
        test.test2();
    #elif TEST_TO_RUN == 3
        test.test3();
    #elif TEST_TO_RUN == 4
        test.test4();
    #elif TEST_TO_RUN == 5
        test.test5();
    #elif TEST_TO_RUN == 6
        test.test6();
    #elif TEST_TO_RUN == 7
        test.test7();
    #elif TEST_TO_RUN == 8
        test.test8();
    #elif TEST_TO_RUN == 9
        test.test9();
    #elif TEST_TO_RUN == 10
        test.test10();
    #elif TEST_TO_RUN == 11
        test.test11();
    #elif TEST_TO_RUN == 12
        test.test12();
    #elif TEST_TO_RUN == 13
        test.test13();
    #elif TEST_TO_RUN == 14
        test.test14();
    #elif TEST_TO_RUN == 15
        test.test15();
    #elif TEST_TO_RUN == 16
        test.test16();
    #elif TEST_TO_RUN == 17
        test.test17();
    #elif TEST_TO_RUN == 18
        test.test18();
    #elif TEST_TO_RUN == 19
        test.test19();
    #elif TEST_TO_RUN == 20
        test.test20();
    #elif TEST_TO_RUN == 21
        test.test21();
    #elif TEST_TO_RUN == 22
        test.test22();
    #elif TEST_TO_RUN == 23
        test.test23();
    #elif TEST_TO_RUN == 24
        test.test24();
    #elif TEST_TO_RUN == 25
        test.test25();
    #elif TEST_TO_RUN == 26
        test.test26();
    #elif TEST_TO_RUN == 27
        test.test27();
    #elif TEST_TO_RUN == 28
        test.test28();
    #elif TEST_TO_RUN == 29
        test.test29();
    #elif TEST_TO_RUN == 30
        test.test30();
    #elif TEST_TO_RUN == 2211
        test.test2211();
    #elif TEST_TO_RUN == 3432
        test.test3432();
    #else
    #error "Unknown TEST_TO_RUN value"
    #endif
}