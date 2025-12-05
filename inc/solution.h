#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include "listnode.h"

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target); // Problem 1
    ListNode* addTwoNumber(ListNode* l1, ListNode* l2); // Problem 2
    int lengthOfLongestSubstring(string s); // Problem 3
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2); // Problem 4
    string longestPalindrome(string s); // Problem 5
    bool isPalindrome(int x); // Problem 9
    int romanToInt(string s); // Problem 13
    string longestCommonPrefix(vector<string>& strs); // Problem 14
    bool isValidParentheses(string s); // Problem 20
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2); // Problem 21
    int countCollisions(string directions); // Problem 2211
    int countPartitions(vector<int>& nums); // Problem 3432
};

#endif // SOLUTION_H