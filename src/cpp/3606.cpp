#include "solution.h"
#include "test.h"
using namespace std;

int approach = 0;

bool isValidChar(char c);
bool isValidStr(string s);

/**
 * Problem 3606: Coupon Code Validator
 * @input: 
 * - code[i]: a string representing the coupon identifier
 * - businessLine[i]: a string denoting the business category of the coupon
 * - isActive[i]: a boolean indicating whether the coupon is currently active
 * NOTE: a coupon[i] is valid if:
 * - code[i] is non-empty & have no specific char (except "_")
 * - businessLine[i] is on of ["electronics", "grocery", "pharmacy", "restaurant"]
 * - isActive[i] is true
 * 
 * @output: array of codes of all valid coupons (sorted by businessLine having the order above, and code)
 */
vector<string> Solution::validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
    if (approach == 1) {
        // Approach 1: Hashmap<string, int> (string for businessLines, int for check valid
        vector<string> valid_codes;
        vector<int> valid_idx;
        int n = max(code.size(), max(businessLine.size(), isActive.size()));
        unordered_map<string, int> line_id;
        line_id["electronics"] = 1;
        line_id["grocery"] = 2;
        line_id["pharmacy"] = 3;
        line_id["restaurant"] = 4;
    
        for (int i = 0; i < n; ++i) {
            if (line_id.find(businessLine[i]) == line_id.end() || code[i].empty() || isActive[i] == false) {
                continue;
            }
    
            // Check valid code
            if (isValidStr(code[i])) {
                valid_idx.push_back(i);
            }
        }
    
        sort(valid_idx.begin(), valid_idx.end(), 
            [&](const int& lhs, const int& rhs) {
                if (line_id.find(businessLine[lhs]) != line_id.find(businessLine[rhs])) {
                    return line_id.find(businessLine[lhs])->second < line_id.find(businessLine[rhs])->second;
                }
                return code[lhs] < code[rhs]; //lexicographical order (ascending)
            }
        );
    
        for(int idx : valid_idx) valid_codes.push_back(code[idx]);
        return valid_codes;
    } else if (approach == 2) {
        // Approach 2: Hashmap<string, vector<string>> (string for businessLines, vector<string> for their valid codes)
        int n = max(code.size(), max(businessLine.size(), isActive.size()));
        vector<string> valid_codes;
        vector<string> categories = {"electronics", "grocery", "pharmacy", "restaurant"};
        unordered_map<string, vector<string>> mp; // key is category, value is valid_codes of them

        for (int i = 0; i < n; ++i) {
            // Guardian
            if (find(categories.begin(), categories.end(), businessLine[i]) == categories.end() ||
                code[i].empty() || 
                !isActive[i] ||
                !isValidStr(code[i])
            ) continue;

            mp[businessLine[i]].push_back(code[i]);
        }

        // Sort
        for (auto& category : categories) {
            if (mp.count(category)) {
                sort(mp[category].begin(), mp[category].end());
                for (auto& c : mp[category]) valid_codes.push_back(c);
            }
        }
        return valid_codes;
    }
    return {};
}

bool isValidChar(char c) {
    return  ('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            ('0' <= c && c <= '9') ||
            (c == '_');
}

bool isValidStr(string s) {
    bool is_valid_str = true;
    for (char c : s) {
        if (isValidChar(c) == false) {
            is_valid_str = false;
            break;
        }
    }
    return is_valid_str;
}

void Test::test3606() {
    cout << "Approach:\n";
    cout << "1. Hashmap<string, int> (string for businessLines, int for check valid\n";
    cout << "2*. Hashmap<string, vector<tring>> (string for businessLines, vector<string> for their valid codes)\n";
    cout << ">>> "; cin >> approach;

    struct Case {
        vector<string> code;
        vector<string> businessLine;
        vector<bool> isActive;
        
        vector<string> exp;
    };

    vector<Case> cases = {
        {{"SAVE20","","PHARMA5","SAVE@20"}, {"restaurant","grocery","pharmacy","restaurant"}, {true,true,true,true}, {"PHARMA5","SAVE20"}},
        {{"GROCERY15","ELECTRONICS_50","DISCOUNT10"}, {"grocery","electronics","invalid"}, {false,true,true}, {"ELECTRONICS_50"}}
    };

    extern Solution sol;

    for (int i = 0; i < (int)cases.size(); ++i) {
        vector<string> res = sol.validateCoupons(cases[i].code, cases[i].businessLine, cases[i].isActive);
        Test::assertTest(res, cases[i].exp, i);
    }
}