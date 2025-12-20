#include "test.h"
#include "global.h"
using namespace std;

#define DEBUG
#define MAX_APR 2
#define APR     2

/**
 * Problem 443: String Compression
 * @input: array of chars. Ex: aabbccc
 * @output: modify the intput array and return the new length of the array. Ex: a2b2c3
*/
int compress(vector<char>& chars) {
    #if APR == 1
    // Create new chars
    if (chars.size() <= 1) return (int)chars.size();

    vector<char> new_chars;
    for (int i = 0; i < (int)chars.size();) {
        int group_len = 1;
        for (int j = i + 1; j < (int)chars.size(); ++j) {
            if (chars[j] == chars[i]) ++group_len;
            else break;
        }
        new_chars.push_back(chars[i]);
        if (group_len > 1) {
            for (char c : to_string(group_len)) {
                new_chars.push_back(c);
            }
        }
        i += group_len;
    }
    chars = new_chars;
    return (int)chars.size();
    #elif APR == 2
    // In place
    int i = 0, res = 0;
    while (i < (int)chars.size()) {
        int group_len = 1;
        while (i + group_len < (int)chars.size() && chars[i + group_len] == chars[i]) {
            ++group_len;
        }

        chars[res++] = chars[i];
        if (group_len > 1) {
            for (char c : to_string(group_len)) {
                chars[res++] = c;
            }
        }
        i += group_len;
    }
    chars.resize(res);
    return res;
    #endif
}

void test443() {
    cout << "Approach " << APR << " / " << MAX_APR << endl;
    
    struct Case {
        vector<char> chars;
        vector<char> exp;
    };

    vector<Case> cases = {
        {{'a','a','b','b','c','c','c'}, {'a','2','b','2','c','3'}},
        {{'a'}, {'a'}},
        {{'a','b','b','b','b','b','b','b','b','b','b','b','b'}, {'a','b','1','2'}},
        {{'a','b','c'}, {'a','b','c'}}
    };

    for (int i = 0; i < (int)cases.size(); ++i) {
        Case c = cases[i];
        compress(c.chars);
        assertTest(c.chars, c.exp, i);
    }
}
