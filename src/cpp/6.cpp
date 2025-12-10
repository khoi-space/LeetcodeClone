#include "solution.h"
#include "test.h"
#include "print.h"
#include <iostream>
using namespace std;

int approach = 0;

/**
 * Problem 6: Zigzag Conversion
 * @input: The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows
        P   A   H   N
        A P L S I I G
        Y   I   R
 * @output: string that read line by line of the input string (such as "PAHNAPLSIIGYIR")
 */
string Solution::convertZigzag(string s, int numRows) {
    if (approach == 1) {
        // Approach 1: Row-wise simulation
        if (numRows == 1 || (int)s.size() <= numRows) return s;
        vector<string> rows(numRows);
        int row = 0, step = 1;
        for (char c : s) {
            rows[row] += c;
            if (row == 0) step = +1; // Move forward
            else if (row == numRows - 1) step = -1; // Move backward
            row += step;
        }

        string result;
        for (const string& r : rows) result += r;
        return result;
    } else if (approach == 2) {
        // Approach 2: Row-by-row Traversal
        if (numRows == 1 || (int)s.size() <= numRows) return s;
        string result;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int row = 0; row < numRows; ++row) {
            for (int i = row; i < n; i += cycleLen) {
                result += s[i];
                // If not first row or last row, make a gap
                int secondIdx = i + cycleLen - 2 * row;
                if (row != 0 && row != numRows - 1 && secondIdx < n) {
                    result += s[secondIdx];
                }
            }
        }
        return result;
    }
    return "";
}

void Test::test6() {
    cout << "Approach:\n";
    cout << "1. Row-wise Simulation\n";
    cout << "2. Row-by-row Traversal\n";
    cout << ">>> "; cin >> approach;
    
    struct Case {
        string s;
        int numRows;
        string exp;
    };

    vector<Case> cases = {
        {"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
        {"PAYPALISHIRING", 4, "PINALSIGYAHRPI"},
        {"A", 1, "A"},
        {"AB", 1, "AB"},
        {"ABC", 2, "ACB"},
        {"", 3, ""},
        {"HELLO", 2, "HLOEL"},
    };

    extern Solution sol;
    bool allPassed = true;

    for (auto& c : cases) {
        string res = sol.convertZigzag(c.s, c.numRows);
        if (res != c.exp) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: res=\"" << res << "\", exp=\"" << c.exp << "\", s=\"" << c.s << "\", numRows=" << c.numRows << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}