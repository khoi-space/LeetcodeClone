#include "solution.h"
#include "test.h"
using namespace std;

/**
 * Problem 20: is Valid Parentheses
 * @input: a string s containing just the characters '(', ')', '{', '}', '[' and ']'
 * @output: determine if the input string is valid.
 */
bool Solution::isValidParentheses(string s) {
    stack<char> st;
    for (char c : s) {
        if(!st.empty()) {
            if (isPair(st.top(), c)) {
                st.pop();
                continue;
            }
        }
        // If !st.empty() or !isPair(last, cur), push cur to st
        st.push(c);
    }
    
    return st.empty();
}

bool isPair(char last, char cur) {
    return  (last == '{' && cur == '}') ||
            (last == '[' && cur == ']') ||
            (last == '(' && cur == ')');
}

void Test::test20() {
    struct Case {
        string s;
        bool exp;
    };
    
    vector<Case> cases = {
        {"()", true},
        {"()[]{}", true},
        {"(]", false},
        {"([)]", false},
        {"{[]}", true},
        {"", true},
        {"(((((", false},
        {"(([]){})", true},
        {"([)", false},
        {"[", false},
        {"]", false}
    };
    
    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        bool res = sol.isValidParentheses(c.s);
        if (res != c.exp) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: s=\"%s\", res=%d, exp=%d\n",
                   c.s.c_str(), res, c.exp);
        }
    }

    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}