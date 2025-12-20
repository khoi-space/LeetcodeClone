#include "test.h"
#include "global.h"
using namespace std;

//#define DEBUG
#define MAX_APR 2
#define APR     2

/**
 * Problem 11: Container With Most Water
 * @input: integer array height of length n
 * There are n vertical lines drawn such that the 2 endpoints of the ith line are (i,0) and (i,height[i])
 * @output: the maximum amount of water a container can store
*/
int maxArea(vector<int>& height) {
#if APR == 1 //O(n^2)
    int _size = height.size();
    int max_area = 0;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (j != i) {
                int min_height = min(height[i], height[j]);
                int width = abs(j - i);
                int area = min_height * width;
                if (area > max_area) max_area = area;
            }
        }
    }
    return max_area;
#elif APR == 2 //O(n)
    // 2 pointers
    int _size = height.size();
    int l = 0;
    int r = _size - 1;
    int max_area = 0;

    while (l < r) {
        int min_height = min(height[l], height[r]);
        int width = r - l;
        int area = min_height * width;
        if (max_area < area) max_area = area;

        if (height[l] < height[r]) ++l;
        else --r;
    }
    return max_area;
#endif
}

void test11() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {
        vector<int> height;
        int exp;
    };

    vector<Case> cases = {
        {{1,8,6,2,5,4,8,3,7}, 49},
        {{1,1}, 1}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        int res = maxArea(c.height);
        assertTest(res, c.exp, i);
    }
}
