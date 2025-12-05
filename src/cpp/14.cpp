#include "solution.h"
#include "test.h"
#include <sstream>
using namespace std;

/**
 * Problem 14: Longest Common Prefix
 * @input: an array of strings
 * @output: the longest common prefix string amongst them
 */
string Solution::longestCommonPrefix(vector<string>& strs) {
    stringstream result;
    if (strs.empty()) return "";
    for (size_t i = 0; i < strs[0].size(); ++i) {
        char c = strs[0][i];
        for (size_t j = 1; j < strs.size(); ++j) {
            if (i >= strs[j].size() || strs[j][i] != c)
                return result.str();
        }
        result << c;
    }
    return result.str();
}

void Test::test14() {
    struct Case {
        vector<string> strs;
        string exp;
    };

    vector<Case> cases = {
        {{"flower","flow","flight"}, "fl"},
        {{"dog","racecar","car"}, ""},
        {{"interview","internet","internal"}, "inter"},
        {{"a"}, "a"},
        {{"",""}, ""},
        {{"ab", "a"}, "a"},
        {{"cir","car"}, "c"},
        {{}, ""}
    };

    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        string res = sol.longestCommonPrefix(const_cast<vector<string>&>(c.strs));
        if (res != c.exp) {
            allPassed = false;
            printf("\033[31mFAILED\033[0m: res=\"%s\", exp=\"%s\"\n",
                   res.c_str(), c.exp.c_str());
        }
    }

    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}