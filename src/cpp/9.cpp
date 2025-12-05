
#include "solution.h"
#include "test.h"
using namespace std;

/**
 * Problem 9: Palindrome Number
 * @input: int x
 * @output: check if x is a palindrome number
 */
bool Solution::isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;

    int rev_num = 0;
    while (x > rev_num) {
        rev_num = rev_num * 10 + x % 10;
        x /= 10;
    }
    
    return (x == rev_num) || (x == rev_num / 10);
}

void Test::test9() {
    struct Case {
        int x;
        bool exp;
    };

    vector<Case> cases = {
        {121, true},      // palindrome dương
        {-121, false},    // âm -> false
        {10, false},      // kết thúc bằng 0 nhưng không phải 0
        {0, true},        // 0 là palindrome
        {12321, true},    // lẻ chữ số
        {1221, true},     // chẵn chữ số
        {123, false}      // không palindrome
    };

    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        bool res = sol.isPalindrome(c.x);
        if (res != c.exp) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: x=%d, res=%d, exp=%d\n", c.x, res, c.exp);
        }
    }

    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}