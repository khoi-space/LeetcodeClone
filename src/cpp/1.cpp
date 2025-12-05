
#include "solution.h"
#include "test.h"
#include "print.h"
#include <iostream>
using namespace std;

int approach = 0;

/**
 * Problem 1: Two Sum
 * @input: given an array of integers nums and an integer target, 
 * @output: indices of the two numbers such that they add up to target.
 */
vector<int> Solution::twoSum(vector<int>& nums, int target) {
    // int appr = 1;
    if (approach == 1) {
        // Approach 1 (optimal): using hash map (O(n)
        unordered_map<int, int> map;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int need = target - nums[i];
    
            if (map.find(need) != map.end()) {
                return {map[need], i};
            }
    
            map[nums[i]] = i; // key=nums[i], value=i
        }
    }
    else if (approach == 2) {
        // Approach 2: brute-force (O(n^2))
        for (int i = 0 ; i < (int)nums.size() - 1; ++i) {
            for (int j = i + 1; j < (int)nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
    }
    return {};
}

void Test::test1() {
    struct Case {
        vector<int> nums;
        int target;
        vector<int> exp;
    };

    vector<Case> cases = {
        {{2,7,8,6,4,3}, 9, {0,1}},
        {{3,2,4}, 6, {1,2}},
        {{3,3}, 6, {0,1}},
        {{1,2,3}, 7, {}}, // no solution
    };

    extern Solution sol;
    bool allPassed = true;

    cout << "Approach:\n";
    cout << "1. Using hash map (*)\n";
    cout << "2. Brute-force\n";
    cout << ">>> "; cin >> approach;
    for (auto& c : cases) {
        vector<int> res = sol.twoSum(c.nums, c.target);
        if (res != c.exp) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: res="; printVector(res);
            cout << ", exp="; printVector(c.exp);
            cout << ", input="; printVector(c.nums);
            cout << ", target=" << c.target << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}