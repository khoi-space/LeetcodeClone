
#include "solution.h"
#include "test.h"
using namespace std;

int approach = 0;

/**
 * Problem 13: Roman to Integer
 * @input: a roman numeral string (I=1, V=5, X=10, L=50, C=100, D=500, M=1000)
 * @output: int of roman numeral string
 */
int Solution::romanToInt(string s) {
    if (approach == 1) {
        // Option 1(optimal): right-left & int array
        static int val[256] = {};
    
        val['I'] = 1;
        val['V'] = 5;
        val['X'] = 10;
        val['L'] = 50;
        val['C'] = 100;
        val['D'] = 500;
        val['M'] = 1000;
    
        int prev_val = 0;
        int result = 0;
    
        for (int i = s.length() - 1; i >= 0; --i) { // Move from right to left (no more jumping)
            int cur_val = val[(unsigned char)s[i]];
            result += (cur_val < prev_val) ? -cur_val : cur_val;
            prev_val = cur_val;
        }
    
        return result;
    }
    else if (approach == 2) {
        // Option 2: left-right & hash map
        unordered_map<char, int> val;
        val['I'] = 1;
        val['V'] = 5;
        val['X'] = 10;
        val['L'] = 50;
        val['C'] = 100;
        val['D'] = 500;
        val['M'] = 1000;
        int result = 0;
    
        for (size_t i = 0; i < s.length(); ++i) { // Move from left to right
            if (i+1 < s.length() && val[s[i]] < val[s[i+1]]) {
                result += val[s[i + 1]] - val[s[i]];
                ++i;
            } else {
                result += val[s[i]];
            }
        }
    
        return result;
    }
    return 0;
}

void Test::test13() {
    struct Case {
        string s;
        int exp;
    };

    vector<Case> cases = {
        {"I", 1},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"IX", 9},
        {"X", 10},
        {"XL", 40},
        {"L", 50},
        {"XC", 90},
        {"C", 100},
        {"CD", 400},
        {"D", 500},
        {"CM", 900},
        {"M", 1000},
        {"LVIII", 58},     // L(50) + V(5) + III(3)
        {"MCMXCIV", 1994}, // M(1000) + CM(900) + XC(90) + IV(4)
    };

    extern Solution sol;
    bool allPassed = true;

    cout << "Approach:\n";
    cout << "1. Righ-to-left & int array (*)\n";
    cout << "2. Left-to-right & hash map\n";
    cout << ">>> "; cin >> approach;
    for (const auto& c : cases) {
        int res = sol.romanToInt(c.s);
        if (res != c.exp) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: s=%s, res=%d, exp=%d\n", c.s.c_str(), res, c.exp);
        }
    }

    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}