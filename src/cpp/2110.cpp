#include "test.h"
#include "global.h"
using namespace std;

/**
 * Problem 2110: Number of Smooth Descent Periods of a Stock
 * @input: a array of the daily price history of stock
 * @output: smooth descent periods
 * @explain: a smooth descent period of a stock if prices[i-1] - prices[i] == 1
 */
long long getDescentPeriods(vector<int>& prices) {
    
    int prev_smth = 0;
    long long sum = prices.size();
    for (int i = 1; i < (int)prices.size(); ++i) {
        if (prices[i-1] - prices[i] == 1) {
            prev_smth++;
            sum += prev_smth;
        } else {
            prev_smth = 0;
        }
    }
    return sum;
}

void test2110() {
    struct Case {
        vector<int> prices;
        long long exp;
    };

    vector<Case> cases = {
        {{3,2,1,4}, 7},
        {{8,6,7,7}, 4},
        {{1}, 1}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        long long res = getDescentPeriods(cases[i].prices);
        assertTest(res, cases[i].exp, i);
    }
}