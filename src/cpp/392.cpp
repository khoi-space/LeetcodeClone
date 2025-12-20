#include "test.h"
#include "global.h"
using namespace std;

//#define DEBUG
#define MAX_APR 2
#define APR     2

/**
 * Problem 392: Is Subsequence
 * @input: two string s and t
 * @output: if s is a subsequence of t or not
 * @example: "ace" is a subsequence of "abcde" while "aec" is not
*/
bool isSubsequence(string s, string t) {
    #if APR == 1
    // Nested Search
    int s_size = s.size();
    int t_size = t.size();
    int j = 0;
    for (int i = 0; i < s_size; ++i) {
        // i will travel on s
        bool char_found = false;
        while (j < t_size) {
            // j will travel on t to find the char == s[i]
            if (t[j] == s[i]) {
                char_found = true;
                ++j;
                break;
            }
            ++j;
        }
        if (char_found == false) return false;
    }
    return true;
    
    #elif APR == 2
    // Two-Pointer
    int s_len = s.length();
    int t_len = t.length();
    int sp = 0;
    int tp = 0;
    while (sp < s_len && tp < t_len) {
        if (t[tp] == s[sp]) {
            ++sp;
        }
        ++tp;
    }
    return sp == s_len;
    #endif
}

void test392() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        string s;
        string t;
        bool exp;
    };

    vector<Case> cases = {
        {"abc", "ahbgdc", true},
        {"axc", "ahbgdc", false},
        {"aaaaaa", "bbaaaa", false}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        bool res = isSubsequence(c.s, c.t);
        assertTest(res, c.exp, i);
    }
}