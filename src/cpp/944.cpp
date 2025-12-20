#include "test.h"
#include "global.h"
using namespace std;

//#define DEBUG
#define MAX_APR 1
#define APR     1

/**
 * Problem 944: Delete Columns to Make Sorted
 * @input: array of n strings, all of the same length
 * @output: the number of columns that are not sorted lexicographically
*/
int minDeletionSize(vector<string>& strs) {
    int strs_size = strs.size();
    int str_len = strs[0].length();
    int cnt = 0;

    for (int i = 0; i < str_len; ++i) { //column i
        for (int j = 1; j < strs_size; ++j) { //word j
            if (strs[j][i] - '0' < strs[j-1][i] - '0') {
                ++cnt;
                // Move to next column
                break;
            }
        }
    }
    return cnt;
}

void test944() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        vector<string> strs;
        int exp;
    };

    vector<Case> cases = {
        {{"cba","daf","ghi"}, 1},
        {{"a","b"}, 0},
        {{"zyx","wvu","tsr"}, 3}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        int res = minDeletionSize(c.strs);
        assertTest(res, c.exp, i);
    }
}
