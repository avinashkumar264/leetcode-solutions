class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {

        // Handle nodes at beginning
        while (head != NULL && head->val == val) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }

        ListNode* prev = NULL;
        ListNode* curr = head;

        while (curr != NULL) {

            if (curr->val == val) {
                prev->next = curr->next;
                ListNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }

        return head;
    }
};