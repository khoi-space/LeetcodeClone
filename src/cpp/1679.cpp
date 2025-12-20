#include "test.h"
#include "global.h"
using namespace std;

//#define DEBUG
#define MAX_APR 2
#define APR     2

/**
 * Problem 1679: Max Number of K-Sum Pairs
 * @input: integer array nums and integer k
 * @rule: in 1 operation, you can pick 2 num from the array whose sum equals k 
 * and remove them from the array
 * @output: the maximum num of operations that can be performed on the array
*/
int maxOperations(vector<int>& nums, int k) {
#if APR == 1 // 2 pointer O(n logn)
    int _size = nums.size();
    int cnt = 0;
    int l = 0;
    int r = _size - 1;

    sort(nums.begin(), nums.end());
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum < k) {
            ++l;
        } else if (sum > k) {
            --r;
        } else {
            ++cnt;
            ++l;
            --r;
        }
    }
    return cnt;
#elif APR == 2 // Use unordered_map O(n)
    unordered_map<int, int> mp;
    int cnt = 0;

    for (int num : nums) {
        int need = k - num;
        if (mp[need] > 0) {
            ++cnt;
            --mp[need];
        } else {
            ++mp[num];
        }
    }
    return cnt;
#endif
}

void test1679() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        vector<int> nums;
        int k;
        int exp;
    };

    vector<Case> cases = {
        {{1,2,3,4}, 5, 2},
        {{3,1,3,4,3}, 6, 1}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        int res = maxOperations(c.nums, c.k);
        debug(c.nums);
        assertTest(res, c.exp, i);
    }
}
