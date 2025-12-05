
#include "solution.h"
#include "test.h"
using namespace std;

/**
 * Prolem 3: Longest Substring Without Repeating Characters
 * @input: a string s
 * @output: the length of the longest substring without duplicate characters
 */
int Solution::lengthOfLongestSubstring(string s) {
    if (s.empty()) return 0;
    
    unordered_set<char> seen;
    int left = 0, right = 0;
    int maxLength = 0;
    
    while (right < (int)s.size()) {
        // If character at right is not in current window
        if (seen.find(s[right]) == seen.end()) {
            seen.insert(s[right]);
            maxLength = max(maxLength, right - left + 1);
            right++;
        } else {
            // Remove characters from left until duplicate is removed
            seen.erase(s[left]);
            left++;
        }
    }
    
    return maxLength;
}

void Test::test3() {
    struct Case {
        string s;
        int exp;
    };

    vector<Case> cases = {
        {"pwwkew", 3},
        {"abcabcbb", 3},
        {"bbbbb", 1},
        {"", 0},
        {"au", 2},
        {"dvdf", 3},
        {"abba", 2},
        {"tmmzuxt", 5},
        {"aab", 2},
        {"abcdef", 6}
    };

    extern Solution sol;
    bool allPassed = true;
    for (const auto& c : cases) {
        int res = sol.lengthOfLongestSubstring(c.s);
        if (res != c.exp) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: s=\"%s\", res=%d, exp=%d\n", c.s.c_str(), res, c.exp);
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}