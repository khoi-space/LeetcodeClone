#include "solution.h"
#include "test.h"
using namespace std;

int approach = 0;

/**
 * Problem 5: Longest Palindromic Substring
 * @input: string s
 * @output: the longest palindromic substring of s
 */
string Solution::longestPalindrome(string s) {
    int appr = 1;
    if (appr == 1) {
        // Approach 1: Check All Substrings - O(n^3)
    } else if (appr == 2) {
        // Approach 2: Dynamic Programming
    } else if (appr == 3) {
        // Approach 3: Expand From Centers
    } else if (appr == 4) {
        // Approach 4: Manacher's Algorithm
    }
    return "";
}

void Test::test5() {
    struct Case {
        string s;
        vector<string> exp; // Accept multiple correct answers
    };

    vector<Case> cases = {
        {"babad", {"bab", "aba"}},
        {"cbbd", {"bb"}},
        {"a", {"a"}},
        {"ac", {"a", "c"}},
        {"racecar", {"racecar"}},
        {"", {""}},
        {"abb", {"bb"}},
    };

    extern Solution sol;
    bool allPassed = true;

    cout << "Approach:\n";
    cout << "1. Check all substrings\n";
    cout << "2. Dynamic programming\n";
    cout << "3. Expand from centers\n";
    cout << "4. Manacher's Algorithm\n";
    cout << ">>> "; cin >> approach;
    for (const auto& c : cases) {
        string res = sol.longestPalindrome(c.s);
        bool match = false;
        for (const auto& e : c.exp) {
            if (res == e) {
                match = true;
                break;
            }
        }
        if (!match) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: s=%s, res=%s, exp=", c.s.c_str(), res.c_str());
            for (const auto& e : c.exp) printf("%s ", e.c_str());
            printf("\n");
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}