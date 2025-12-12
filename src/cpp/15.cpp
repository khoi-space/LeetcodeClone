#include "solution.h"
#include "test.h"
using namespace std;

int approach = 0;

/**
 * Problem 15: 3Sum
 * @input: an integer array nums
 * @output: all the triplet that have sum == 0
 */
vector<vector<int>> Solution::threeSum(vector<int>& nums) {
    if (approach == 1) {
        // Approach 1: 3 nested loops
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
    
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> satisfy_sum_arr = {nums[i], nums[j], nums[k]};
                        bool arrExsited = false;
                        for (int l = 0; l < (int)ans.size(); ++l) {
                            if (satisfy_sum_arr == ans[l]) {
                                arrExsited = true;
                                break;
                            }
                        }
                        if (arrExsited == false) {
                            ans.push_back(satisfy_sum_arr);
                        }
                    }
                }
            }
        }
        return ans;
    } else if (approach == 2) {
        // Approach 2: Two pointers
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int total = nums[i] + nums[j] + nums[k];

                if (total > 0) {
                    --k;
                } else if (total < 0) {
                    ++j;
                } else { // total == 0
                    ans.push_back({nums[i], nums[j], nums[k]});
                    ++j;

                    while (nums[j] == nums[j-1] && j < k) {
                        ++j;
                    }
                }
            }
        }
        return ans;
    }
    return {};
}

void Test::test15() {
    cout << "Approach:\n";
    cout << "1. 3 nested loops - O(n^3)\n";
    cout << "2*. Two pointer - O(n^2)\n";
    cout << ">>> "; cin >> approach;

    struct Case {
      vector<int> nums;
      vector<vector<int>> exp;  
    };

    vector<Case> cases = {
      // 0. Basic
      {{-1,0,1,2,-1,-4}, {{-1,-1,2},{-1,0,1}}},
      // 1. No solution
      {{1,2,3,4,5}, {}},
      // 2. All zeros
      {{0,0,0,0}, {{0,0,0}}},
      // 3. Duplicates
      {{-2,0,0,2,2}, {{-2,0,2}}},
      // 4. Large negatives and positives
      {{-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6}, {{-4,-2,6},{-4,0,4},{-4,1,3},{-4,2,2},{-2,-2,4},{-2,0,2}}},
      // 5. Only two numbers
      {{0,1}, {}},
      // 6. Only one number
      {{0}, {}},
      // 7. Empty
      { {}, {} },
      // 8. All positive
      {{1,1,1,1}, {}},
      // 9. All negative
      {{-1,-1,-1,-1}, {}},
      // 10. Mix with zero
      {{-2,0,2,2,0,-2}, {{-2,0,2}}},
      // 11. Multiple zeros
      {{0,0,0}, {{0,0,0}}},
      // 12. Large input
      {{-1,0,1,2,-1,-4,-2,-2,3,0,4}, {{-4,0,4},{-4,1,3},{-2,-2,4},{-2,-1,3},{-2,0,2},{-1,-1,2},{-1,0,1}}},
      // 13. Triplets with same value
      {{1,1,-2}, {{-2,1,1}}},
      // 14. Triplets with zero and duplicates
      {{0,0,0,0,0}, {{0,0,0}}},
    };

    extern Solution sol;
    for (int i = 0; i < (int)cases.size(); ++i) {
        vector<vector<int>> res = sol.threeSum(cases[i].nums);
        Test::assertTest(res, cases[i].exp, i);
    }
}