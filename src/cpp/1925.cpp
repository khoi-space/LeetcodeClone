#include "test.h"
#include "global.h"
using namespace std;
/**
 * Problem 1925: Count Square Sum Triples
 * @input: integer n
 * @output: num of square triples in n
 * @explain: square triple (a, b, c) is where a^2 + b^2 = c^2
*/
int countTriples(int n) {
    int cnt = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            int c = sqrt(a*a + b*b);
            if (c <= n && c*c == a*a + b*b) ++cnt;
        }
    }
    return cnt;
}


void test1925() {
    struct Case {
        int n;
        int exp;
    };

    vector<Case> cases = {
        {5, 2},
        {10, 4}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        int res = countTriples(cases[i].n);
        assertTest(res, cases[i].exp, i);
    }
}
