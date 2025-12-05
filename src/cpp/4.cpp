
#include "solution.h"
#include "test.h"
using namespace std;

int approach = 0;

// Helper function
int solve(vector<int>& A, vector<int>& B, int k, int a_start, int a_end, int b_start, int b_end);

/**
 * Problem 4: Median of Two Sorted Arrays
 * @input: two sorted arrays nums1 and nums2 of size m and n respectively
 * @output: the median of the two sorted arrays
 * @require: must be O(log(m+n))
 */
double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (approach == 1) {
        // Approach 1: Merge Sort - O(m+n)
        int p1 = 0, p2 = 0;

        auto getMin = [&](vector<int>& nums1, vector<int>& nums2) -> int {
            // Get the min(nums1[p1], nums2[p2]) and increment its pointer
            if (p1 < (int)(nums1.size()) && p2 < (int)(nums2.size())) {
                return (nums1[p1] < nums2[p2]) ? nums1[p1++] : nums2[p2++];
            } else if (p1 < (int)(nums1.size())) {
                return nums1[p1++];
            } else if (p2 < (int)(nums2.size())) {
                return nums2[p2++];
            }
            return -1;
        };
        
        int total_size = (int)(nums1.size() + nums2.size());
        if (total_size % 2 == 0) {
            for (int i = 0; i < total_size / 2 - 1; ++i) {
                getMin(nums1, nums2);
            }
            return (double)(getMin(nums1, nums2) + getMin(nums1, nums2)) / 2;
        } else {
            for (int i = 0; i < total_size / 2; ++i) {
                getMin(nums1, nums2);
            }
            return getMin(nums1, nums2);
        }
    }
    else if (approach == 2) {
        // Approach 2: Binary Search, Recursive - O(log(min(m, n)))
        int n = (int)(nums1.size()), m = (int)(nums2.size());
        int total_size = n + m;
        if (total_size % 2) {
            return (double)(solve(nums1, nums2, total_size / 2, 0, n - 1, 0, m - 1));
        } else {
            return (double)(solve(nums1, nums2, total_size / 2 - 1, 0, n - 1, 0, m - 1)
                            + solve(nums1, nums2, total_size / 2, 0, n - 1, 0, m - 1))
                            / 2;
        }
    }
    return -1;
}

int solve(  vector<int>& A, vector<int>& B, int k, 
            int a_start, int a_end, 
            int b_start, int b_end) {
    // If the segment of on array is empty, it means we have passed all its element
    if (a_end < a_start) {
        return B[k - a_start];
    }
    if (b_end < b_start) {
        return A[k - b_start];
    }

    // Get the middle idx and middle val of A and B
    int a_idx = (a_start + a_end) / 2, b_idx = (b_start + b_end) / 2;
    int a_val = A[a_idx], b_val = B[b_idx];

    // If k is in the right half of A+B, remove the smaller left half
    if (a_idx + b_idx < k) {
        if (a_val > b_val) {
            return solve(A, B, k, a_start, a_end, b_idx + 1, b_end);
        } else {
            return solve(A, B, k, a_idx + 1, a_end, b_start, b_end);
        }
    }
    // Otherwise, remove the larger right half
    else {
        if (a_val > b_val) {
            return solve(A, B, k, a_start, a_idx - 1, b_start, b_end);
        } else {
            return solve(A, B, k, a_start, a_end, b_start, b_idx - 1);
        }
    }
    return -1;
}

void Test::test4() {
    struct Case {
        vector<int> nums1;
        vector<int> nums2;
        double exp;
    };

    vector<Case> cases = {
        {{1,3}, {2}, 2.0},
        {{1,2}, {3,4}, 2.5},
        {{0,0}, {0,0}, 0.0},
        {{}, {1}, 1.0},
        {{2}, {}, 2.0},
        {{1,3,5}, {2,4,6}, 3.5},
        {{1}, {2,3,4,5,6}, 3.5},
        {{}, {2,3}, 2.5},
        {{1000000}, {1000001}, 1000000.5},
        {{1,2,3,4,5}, {6,7,8,9,10}, 5.5}
    };

    extern Solution sol;
    bool allPassed = true;

    cout << "Approach:\n";
    cout << "1. Merge Sort\n";
    cout << "2. Binary Search + Recursive (*)\n";
    cout <<">>> "; cin >> approach;
    for (const auto& c : cases) {
        double res = sol.findMedianSortedArrays(const_cast<vector<int>&>(c.nums1), const_cast<vector<int>&>(c.nums2));
            if (std::fabs(res - c.exp) > 1e-6) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: res=" << res << ", exp=" << c.exp;
            cout << ", nums1="; for (int x : c.nums1) cout << x << ' ';
            cout << ", nums2="; for (int x : c.nums2) cout << x << ' ';
            cout << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}
