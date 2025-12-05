
#include "solution.h"
#include "test.h"
#include "print.h"
// #include "listnode.h"
using namespace std;

/**
 * Problem 2: Add Two Numbers
 * @input: two non-empty linked lists representing two non-negative integers (reserve ordered)
 * @output: the sum as a linked list
 */
ListNode* Solution::addTwoNumber(ListNode* l1, ListNode* l2) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* curr = dummyHead;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry) {
        int x = (l1 != nullptr) ? l1->val : 0;
        int y = (l2 != nullptr) ? l2->val : 0;
        int sum = x + y + carry;
        curr->next = new ListNode(sum % 10);
        carry = sum / 10;
        curr = curr->next;
        l1 = (l1 != nullptr) ? l1->next : nullptr;
        l2 = (l2 != nullptr) ? l2->next : nullptr;
    }
    return dummyHead->next;
}

void Test::test2() {
    struct Case {
        vector<int> arr1;
        vector<int> arr2;
        vector<int> exp;
    };

    vector<Case> cases = {
        {{9,9,9,9}, {1}, {0,0,0,0,1}},
        {{2,4,3}, {5,6,4}, {7,0,8}},
        {{0}, {0}, {0}},
        {{1,8}, {0}, {1,8}},
        {{5}, {5}, {0,1}},
    };

    extern Solution sol;
    bool allPassed = true;

    for (const auto& c : cases) {
        ListNode* l1 = ListNode::createList(c.arr1.data(), c.arr1.size());
        ListNode* l2 = ListNode::createList(c.arr2.data(), c.arr2.size());
        ListNode* exp = ListNode::createList(c.exp.data(), c.exp.size());
        ListNode* res = sol.addTwoNumber(l1, l2);
        if (!ListNode::compareList(res, exp)) {
            allPassed = false;
            cout << "\033[31mFAILED\033[0m: ";
            cout << "res="; if(res) res->printList(); else cout << "nullptr";
            cout << ", exp="; if(exp) exp->printList(); else cout << "nullptr";
            cout << ", arr1="; printVector(c.arr1);
            cout << ", arr2="; printVector(c.arr2);
            cout << endl;
        }
    }
    if (allPassed) {
        cout << "\033[32mPASSED\033[0m\n";
    }
}