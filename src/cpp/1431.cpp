#include "test.h"
#include "global.h"
using namespace std;

//int approach = 0;

/**
 * Problem 1431: Kids With the Greatest Number of Candies
 * @input: candies[i] is the num of candies that ith kids has, extraCandies is the num of candies you have
 * @output: boolean array that each kid after giving the extraCandies have the greatest number of candies among all the kids
 * @note: 
 * - Every time giving the extraCandies, we will find the kids with the greatest candies, not after giving all kids the extraCandies.
 * - Each kid will have the same extraCandies.
*/
vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int max_candies = 0;
    for (int candy : candies) {
        if (candy > max_candies) {
            max_candies = candy;
        }
    }

    vector<bool> res;
    for (int candy : candies) {
        res.push_back(candy + extraCandies >= max_candies);
    }
    return res;
}

void test1431() {
    //cout << "Approach:";
    //cout << "1.";
    //cout << "2.";
    //cout << ">>> "; cin >> approach;

    struct Case {
        vector<int> candies;
        int extraCandies;
        vector<bool> exp;
    };

    vector<Case> cases = {
        {{2,3,5,1,3}, 3, {true,true,true,false,true}},
        {{4,2,1,1,2}, 1, {true,false,false,false,false}},
        {{12,1,12}, 10, {true,false,true}},
        {{2,8,7}, 1, {false,true,true}}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        // res
        vector<bool> res = kidsWithCandies(cases[i].candies, cases[i].extraCandies);
        assertTest(res, cases[i].exp, i);
    }
}
