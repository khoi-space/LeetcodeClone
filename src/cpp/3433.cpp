#include "solution.h"
#include "test.h"
using namespace std;

#define STATUS      0
#define TIMESTAMP   1
#define MENTION     2
#define ID          2

/**
 * Problem 3433: Count Mentions Per Users
 * @input: 2 types
 * - Message Event: ["MESSAGE", "timestamp_i", "mentions_string_i"] //ig. ["MESSAGE", "10", "id1 id0"]
 *  * Note: mentions_string can be: IDs (even the offline users), "ALL" (all users), "HERE" (all online users)
 * - Offline Event: ["OFFLINE", "timestamp_i", "id_i"] //ig. ["OFFLINE", "11", "0"]
 *  * Note: the user will automatically be online again at time timestamp_i + 60
 * @output: an array {mentions} where {mentions[i]} represents the number of mentions the user with id {i} has
 */
vector<int> Solution::countMentions(int numberOfUsers, vector<vector<string>>& events) {
    vector<int> count(numberOfUsers);
    vector<int> next_online_time(numberOfUsers);
    // Sort events by timestamp
    // If 2 events has the same time, "OFFLINE" status has higher prio
    sort(events.begin(), events.end(),
        [&](const vector<string>& lhs, const vector<string>& rhs) {
            int lhs_timestamp = stoi(lhs[TIMESTAMP]);
            int rhs_timestamp = stoi(rhs[TIMESTAMP]);
            if (lhs_timestamp != rhs_timestamp) {
                return lhs_timestamp < rhs_timestamp;
            }
            if (rhs[STATUS] == "OFFLINE") {
                return false;
            }
            return true;
        }
    );

    for (auto& event : events) {
        int cur_time = stoi(event[TIMESTAMP]);
        if (event[STATUS] == "MESSAGE") {
            if (event[MENTION] == "ALL") {
                // Mention all users
                for (int i = 0; i < numberOfUsers; ++i) {
                    ++count[i];
                }
            } else if (event[MENTION] == "HERE") {
                // Mention all ONLINE users
                for (int i = 0; i < numberOfUsers; ++i) {
                    if (next_online_time[i] <= cur_time) {
                        ++count[i];
                    }
                }
            } else {
                // Mention specific IDs
                int mentioned_id = 0;
                for (int i = 0; i < (int)event[MENTION].size(); ++i) {
                    if (isdigit(event[MENTION][i])) {
                        mentioned_id = mentioned_id * 10 + (event[MENTION][i] - '0'); // multiple 10 to handle with id higher than 9
                    }
                    if (i + 1 == (int)event[2].size() || 
                        event[MENTION][i + 1] == ' ') {
                            ++count[mentioned_id];
                            mentioned_id = 0;
                        }
                }
            }
        } else if (event[STATUS] == "OFFLINE") {
            int id = stoi(event[ID]);
            next_online_time[id] = cur_time + 60;
        } else {
            cout << "INVALID status\n";
            continue;
        }
    }
    return count;
}

void Test::test3433() {
    struct Case {
        // Input
        int numberOfUsers;
        vector<vector<string>> events;
        // Output
        vector<int> exp;
    };

    vector<Case> cases = {
        // 1. No events
        {2, {}, {0,0}},
        // 2. One MESSAGE, no mentions
        {2, {{"MESSAGE", "1", ""}}, {0,0}},
        // 3. One MESSAGE, mention one user
        {2, {{"MESSAGE", "1", "id0"}}, {1,0}},
        // 4. One MESSAGE, mention two users
        {2, {{"MESSAGE", "1", "id0 id1"}}, {1,1}},
        // 5. One MESSAGE, mention ALL
        {2, {{"MESSAGE", "1", "ALL"}}, {1,1}},
        // 6. One MESSAGE, mention HERE (all online)
        {2, {{"MESSAGE", "1", "HERE"}}, {1,1}},
        // 7. id0 offline, HERE only mentions id1
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "2", "HERE"}}, {0,1}},
        // 8. id0 offline, ALL mentions both
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "2", "ALL"}}, {1,1}},
        // 9. id0 offline at 1, online at 61, HERE at 62 (both online)
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "62", "HERE"}}, {1,1}},
        // 10. id0:1 (direct), id1:1 (HERE), id0:1 (ALL), id1:1 (ALL) => {2,2}
        {2, {{"MESSAGE", "1", "id0"}, {"OFFLINE", "2", "1"}, {"MESSAGE", "3", "HERE"}, {"MESSAGE", "4", "ALL"}}, {3,1}},
        // 11. both offline, HERE mentions none
        {2, {{"OFFLINE", "1", "0"}, {"OFFLINE", "1", "1"}, {"MESSAGE", "2", "HERE"}}, {0,0}},
        // 12. both offline, ALL mentions both
        {2, {{"OFFLINE", "1", "0"}, {"OFFLINE", "1", "1"}, {"MESSAGE", "2", "ALL"}}, {1,1}},
        // 13. id0 offline, id0:1 (direct, even offline), id1:1 (direct)
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "2", "id0"}, {"MESSAGE", "3", "id1"}}, {1,1}},
        // 14. id0 offline, HERE at 2 (only id1), HERE at 62 (both online)
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "2", "HERE"}, {"MESSAGE", "62", "HERE"}}, {1,2}},
        // 15. ALL (all 3), id1 offline, HERE (id0,id2), id2 (direct)
        {3, {{"MESSAGE", "1", "ALL"}, {"OFFLINE", "2", "1"}, {"MESSAGE", "3", "HERE"}, {"MESSAGE", "4", "id2"}}, {2,1,3}},
        // 16. id0 offline, id1 offline, HERE (none)
        {2, {{"OFFLINE", "1", "0"}, {"OFFLINE", "2", "1"}, {"MESSAGE", "3", "HERE"}}, {0,0}},
        // 17. id0 offline, HERE at 62 (both online), id1 offline, HERE at 64 (only id0)
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "62", "HERE"}, {"OFFLINE", "63", "1"}, {"MESSAGE", "64", "HERE"}}, {2,1}},
        // 18. id0 offline, id1:1 (direct), id1 offline, ALL (id0 online only)
        {2, {{"OFFLINE", "1", "0"}, {"MESSAGE", "2", "id1"}, {"OFFLINE", "3", "1"}, {"MESSAGE", "4", "ALL"}}, {1,2}},
        // 19. mention id3 (not in system)
        {4, {{"MESSAGE", "1", "id3"}}, {0,0,0,1}},
        // 20. ALL (both), HERE (both)
        {2, {{"MESSAGE", "1", "ALL"}, {"MESSAGE", "2", "HERE"}}, {2,2}}
    };

    extern Solution sol;

    int i = 0;
    for (auto& c : cases) {
        ++i;
        vector<int> res = sol.countMentions(c.numberOfUsers, c.events);
        Test::assertTest(res, c.exp, i);
    }

}