#include "test.h"
#include "global.h"
using namespace std;

#define DEBUG
#define MAX_APR 1
#define APR     1

/**
 * Problem 643: Maximum Average Subarray I
 * @input: integer array nums, integer k
 * @output: find a contiguous subarray of length k that has the max avg
*/
double findMaxAverage(vector<int>& nums, int k) {
    long int cur_sum = 0, max_sum = 0;

    // Init cur_sum and max_sum of the first k elements
    for (int i = 0; i < k; ++i) {
        cur_sum += nums[i];
    }
    max_sum = cur_sum;

    for (int i = k; i < (int)nums.size(); ++i) {
        // Subtract the left element of the window
        // Add the right element of the window
        cur_sum += nums[i];
        cur_sum -= nums[i - k];

        max_sum = max(max_sum, cur_sum);
    }
    return (double)max_sum / k;
}

void test643() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        vector<int> nums;
        int k;
        double exp;
    };

    vector<Case> cases = {
        {{1,12,-5,-6,50,3}, 4, 12.75000},
        {{5}, 1, 5.00000},
        {{0,1,1,3,3}, 4, 2.00000}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        double res = findMaxAverage(c.nums, c.k);
        assertTest(res, c.exp, i);
    }
}
