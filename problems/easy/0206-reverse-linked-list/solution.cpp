class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* next = curr->next; // store next
            curr->next = prev;           // reverse link
            prev = curr;                 // move prev
            curr = next;                 // move curr
        }

        return prev;
    }
};