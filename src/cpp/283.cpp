#include "test.h"
#include "global.h"
using namespace std;

#define DEBUG
#define MAX_APR 1
#define APR     1

/**
 * Problem 283: Move Zeroes
 * @input: integer array
 * @output: move all 0's to the end of it in order-reserve of other elements
 * @rule: must in-place
*/
void moveZeroes(vector<int> &nums) {
    int n = nums.size();
    int l = 0;
    for (int r = 0; r < n; ++r) {
        if (nums[r] != 0) {
            swap(nums[r], nums[l]);
            ++l;
            #ifdef DEBUG
            debug(nums);
            #endif
        }
    }
}

void test283() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        vector<int> nums;
        vector<int> exp;
    };

    vector<Case> cases = {
        {{0,1,0,3,12}, {1,3,12,0,0}},
        {{0}, {0}},
        {{1,1,0,1,1}, {1,1,1,1,0}}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        moveZeroes(c.nums);
        assertTest(c.nums, c.exp, i);
    }
}
