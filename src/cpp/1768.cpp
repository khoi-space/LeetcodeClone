#include "test.h"
#include "global.h"
using namespace std;
/**
 * Problem 1768: Merge Strings Alternately
*/
string mergeAlternately(string word1, string word2) {
    string ans = "";
    int idx1 = 0;
    int idx2 = 0;
    while (idx1 < (int)word1.size() || idx2 < (int)word2.size()) {
        if (idx1 < (int)word1.size()) {
            ans += word1[idx1];
            ++idx1;
        }
        if (idx2 < (int)word2.size()) {
            ans += word2[idx2];
            ++idx2;
        }
    }
    return ans;
}

void test1768() {
    struct Case {
        string word1;
        string word2;
        string exp;
    };

    vector<Case> cases = {
        {"abc", "pqr", "apbqcr"},
        {"ab", "pqrs", "apbqrs"},
        {"abcd", "pq", "apbqcd"}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        string res = mergeAlternately(cases[i].word1, cases[i].word2);
        assertTest(res, cases[i].exp, i);
    }
}
