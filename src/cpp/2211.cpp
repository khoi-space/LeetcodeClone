#include "solution.h"
#include "test.h"
#include <iostream>
using namespace std;

int approach = 0;

/**
 * Problem 2211: Count Collision on a Road
 * @desc: Cars run at same speed. 
 *  Count += 2 if two cars move in opposite dir
 *  Count += 1 if one car stays and collides with another car
 * @dict: 'L' - left, 'R' - right, 'S' - stay
 * @input: a string of direction of each car
 * @output: number of collisions
 */
int Solution::countCollisions(string directions) {
    if (approach == 1) {
        // Approach 1: Simulation
        int collisionCount = 0;
        int rightMovingCount = -1;
        for (char direction : directions) {
            if (direction == 'L') {
                if (rightMovingCount >= 0) {
                    collisionCount += rightMovingCount + 1;
                    rightMovingCount = 0;
                }
            } else if (direction == 'S') {
                if (rightMovingCount > 0) {
                    collisionCount += rightMovingCount;
                }
                rightMovingCount = 0;
            } else if (direction == 'R') {
                if (rightMovingCount >= 0) {
                    ++rightMovingCount;
                } else {
                    rightMovingCount = 1;
                }
            } else {
                return -1;
            }
        }
        return collisionCount;
    }
    else if (approach == 2) {
        // Approach 2: Counting
        int collisionCount = 0;
        int n = directions.size();
        int l = 0, r = n - 1;
        // Skip all left at head
        while (l < n && directions[l] == 'L') {
            ++l;
        }
        // Skip all right at tail
        while (r >= l && directions[r] == 'R') {
            --r;
        }

        // Count values that not 'S' in the rest
        for (int i = l; i <= r; ++i) {
            char d = directions[i];
            if (d == 'S') continue;
            if (d != 'L' && d != 'R') return -1; // Invalid
            ++collisionCount;
        }
        return collisionCount;
    }
    return 0;
}

void Test::test2211() {
    cout << "Approach:\n";
    cout << "1. Simulation\n";
    cout << "2. Counting\n";
    cout << ">>> "; cin >> approach;

    struct Case {
        string directions;
        int exp;
    };

    vector<Case> cases = {
        {"RLRSLL", 5},
        {"LLRR", 0},
        {"SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR", 20},
        {"S", 0},
        {"R", 0},
        {"L", 0},
        {"RS", 1},
        {"SL", 1},
        {"RRLL", 4},
        {"RRSLL", 4},
        {"LRLSL", 3},
        {"RLRL", 4},
        {"SR", 0},
        {"LS", 0},
        {"SSSS", 0},
        {"", 0},
        {"RRS", 2},
        {"LLS", 0},
        {"SRS", 1},
        {"RSL", 2},
        {"RXRL", -1} // Invalid directions
    };

    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        int res = sol.countCollisions(c.directions);
        if (res != c.exp) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: ";
            cout << c.directions << " | res= " << res << ", exp= " << c.exp;
            cout << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}

 