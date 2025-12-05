#include "solution.h"
#include "test.h"
#include "print.h"
#include <iostream>
using namespace std;

int approach = 0;

/**
 * Problem 3432: Count Partitions with Even Sum Difference
 * @input: vector<int> nums
 * @output: num of partitions where sum_left - sum_right is even
 */
int Solution::countPartitions(vector<int>& nums) {
    if (approach == 1) {
        // Approach 1: Mathematics
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        return totalSum % 2 == 0 ? nums.size() - 1 : 0;
    } else if (approach == 2) {
        // Approach 2: Parity counting
        int oddCount = 0;
        for (int num : nums) {
            if (num % 2 != 0) {
                ++oddCount;
            }
        }
        return (oddCount % 2 == 0) ? nums.size() - 1 : 0;
    } else if (approach == 3) {
        // Approach 3: Prefix parity scan
        bool totalOdd = false;
        for (int num : nums) {
            if (num % 2 != 0) {
                totalOdd = !totalOdd;
            }
        }

        bool prefixOdd = false;
        int partitions = 0;
        for (size_t i = 0; i + 1 < nums.size(); ++i) {
            if (nums[i] % 2 != 0) {
                prefixOdd = !prefixOdd;
            }
            bool suffixOdd = totalOdd ^ prefixOdd;
            if (prefixOdd == suffixOdd) {
                ++partitions;
            }
        }
        return partitions;
    }
    return 0;
}

void Test::test3432() {
    cout << "Approach:\n";
    cout << "1. Mathematics\n";
    cout << "2. Parity counting\n";
    cout << "3. Prefix parity scan\n";
    cout << ">>> "; cin >> approach;

    struct Case {
        vector<int> nums;
        int exp;
    };

    vector<Case> cases = {
        {{1, 2}, 0},
        {{1, 1}, 1},
        {{2, 4, 6}, 2},
        {{3, 5, 7}, 0},
        {{0, 0, 0, 0}, 3},
        {{10}, 0},
        {{1, 2, 3, 4}, 3},
        {{1, 3, 5, 7}, 3},
        {{2, 3, 5, 8, 13}, 0},
        {{1000000000, 1000000000}, 1},
        {{1, -1, 1, -1}, 3},
        {{4, 4, 4, 4, 4, 4}, 5},
        {{1, 0, 1}, 2},
        {{5, -3, 2}, 2},
        {{9, -4, -5}, 2},
        {{7, 7, 7, 7, 7}, 0},
        {{2, 2, 2, 2, 3}, 0},
        {{2, 2, 2, 2, 2}, 4},
        {{1, 2, 3, 4, 5, 6}, 0},
        {{8, 1, 1, 8}, 3},
    };
    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        vector<int> numsCopy = c.nums;
        int res = sol.countPartitions(numsCopy);
        if (res != c.exp) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: input=";
            printVector(c.nums);
            cout << " | res=" << res << " | exp=" << c.exp << '\n';
        }
    }

    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}