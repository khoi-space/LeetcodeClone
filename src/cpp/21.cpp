#include "solution.h"
#include "test.h"
#include "print.h"
using namespace std;

int approach = 0;

/**
 * Problem 21: 
 * @input: the heads of two sorted linked lists list1 and list2
 * @output: the head of the merged linked list (sorted)
 */
ListNode* Solution::mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (approach == 1) {
        // Approach 1: recursion
        if (list1 == nullptr || list2 == nullptr) {
            return list1 ? list1 : list2;
        }

        if (list1->val > list2->val) {
            swap(list1, list2);
        }

        list1->next = mergeTwoLists(list1->next, list2);

        return list1;
    }
    else if (approach == 2) {
        // Approach 2: dummy node
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;

        while (list1 && list2) {
            if (list1->val > list2->val) {
                cur->next = list2;
                list2 = list2->next;
            } else {
                cur->next = list1;
                list1 = list1->next;
            }
            cur = cur->next;
        }

        cur->next = (list1 != nullptr) ? list1 : list2;

        ListNode* head = dummy->next;
        delete dummy;
        return head;
    }
    return nullptr;
}

void Test::test21() {
    cout << "Approach:\n";
    cout << "1. Recursion\n";
    cout << "2. Dummy node\n";
    cout << ">>> "; cin >> approach;
    
    struct Case {
        vector<int> list1;
        vector<int> list2;
        vector<int> exp;
    };

    vector<Case> cases = {
        {{1,2,4}, {1,3,4}, {1,1,2,3,4,4}},
        {{}, {}, {}},
        {{}, {0}, {0}},
        {{2}, {1}, {1,2}},
        {{1,3,5}, {2,4,6}, {1,2,3,4,5,6}},
        {{1,2,3}, {}, {1,2,3}},
        {{}, {1,2,3}, {1,2,3}},
        {{5,6,7}, {1,2,3}, {1,2,3,5,6,7}},
        {{1,1,1}, {1,1,1}, {1,1,1,1,1,1}}
    };

    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        ListNode* l1 = ListNode::createList(c.list1.data(), c.list1.size());
        ListNode* l2 = ListNode::createList(c.list2.data(), c.list2.size());
        ListNode* exp = ListNode::createList(c.exp.data(), c.exp.size());
        ListNode* res = sol.mergeTwoLists(l1, l2);
        if (!ListNode::compareList(res, exp)) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: ";
            cout << "res="; if(res) res->printList(); else cout << "nullptr";
            cout << ", exp="; if(exp) exp->printList(); else cout << "nullptr";
            cout << ", list1="; printVector(c.list1);
            cout << ", list2="; printVector(c.list2);
            cout << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}