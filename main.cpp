#include "test.h"
#include "global.h"
#include <cstring>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    #ifndef TEST_TO_RUN
    #define TEST_TO_RUN 0
    #endif

    #if TEST_TO_RUN == 1
        test1();
    #elif TEST_TO_RUN == 2
        test2();
    #elif TEST_TO_RUN == 3
        test3();
    #elif TEST_TO_RUN == 4
        test4();
    #elif TEST_TO_RUN == 5
        test5();
    #elif TEST_TO_RUN == 6
        test6();
    #elif TEST_TO_RUN == 7
        test7();
    #elif TEST_TO_RUN == 8
        test8();
    #elif TEST_TO_RUN == 9
        test9();
    #elif TEST_TO_RUN == 10
        test10();
    #elif TEST_TO_RUN == 11
        test11();
    #elif TEST_TO_RUN == 12
        test12();
    #elif TEST_TO_RUN == 13
        test13();
    #elif TEST_TO_RUN == 14
        test14();
    #elif TEST_TO_RUN == 15
        test15();
    #elif TEST_TO_RUN == 16
        test16();
    #elif TEST_TO_RUN == 17
        test17();
    #elif TEST_TO_RUN == 18
        test18();
    #elif TEST_TO_RUN == 19
        test19();
    #elif TEST_TO_RUN == 20
        test20();
    #elif TEST_TO_RUN == 21
        test21();
    #elif TEST_TO_RUN == 22
        test22();
    #elif TEST_TO_RUN == 23
        test23();
    #elif TEST_TO_RUN == 24
        test24();
    #elif TEST_TO_RUN == 25
        test25();
    #elif TEST_TO_RUN == 26
        test26();
    #elif TEST_TO_RUN == 27
        test27();
    #elif TEST_TO_RUN == 28
        test28();
    #elif TEST_TO_RUN == 29
        test29();
    #elif TEST_TO_RUN == 30
        test30();
    #elif TEST_TO_RUN == 67
        test67();
    #elif TEST_TO_RUN == 151
        test151();
    #elif TEST_TO_RUN == 162
        test162();
    #elif TEST_TO_RUN == 238
        test238();
    #elif TEST_TO_RUN == 283
        test283();
    #elif TEST_TO_RUN == 334
        test334();
    #elif TEST_TO_RUN == 345
        test345();
    #elif TEST_TO_RUN == 392
        test392();
    #elif TEST_TO_RUN == 443
        test443();
    #elif TEST_TO_RUN == 605
        test605();
    #elif TEST_TO_RUN == 643
        test643();
    #elif TEST_TO_RUN == 944
        test944();
    #elif TEST_TO_RUN == 1071
        test1071();
    #elif TEST_TO_RUN == 1431
        test1431();
    #elif TEST_TO_RUN == 1523
        test1523();
    #elif TEST_TO_RUN == 1679
        test1679();
    #elif TEST_TO_RUN == 1768
        test1768();
    #elif TEST_TO_RUN == 1925
        test1925();
    #elif TEST_TO_RUN == 1957
        test1957();
    #elif TEST_TO_RUN == 2110
        test2110();
    #elif TEST_TO_RUN == 2210
        test2210();
    #elif TEST_TO_RUN == 2211
        test2211();
    #elif TEST_TO_RUN == 3432
        test3432();
    #elif TEST_TO_RUN == 3433
        test3433();
    #elif TEST_TO_RUN == 3487
        test3487();
    #elif TEST_TO_RUN == 3606
        test3606();
    #else
        #error "Unknown TEST_TO_RUN value"
    #endif
    return 0;
}