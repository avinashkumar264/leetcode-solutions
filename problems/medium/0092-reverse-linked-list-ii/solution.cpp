class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        // Edge case
        if (head == nullptr || left == right)
            return head;

        // Step 1: Create dummy node
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;

        // Step 2: Move prev to node before 'left'
        for (int i = 1; i < left; i++) {
            prev = prev->next;
        }

        // Step 3: Start reversing
        ListNode* curr = prev->next;

        for (int i = 0; i < right - left; i++) {

            ListNode* forward = curr->next;

            curr->next = forward->next;

            forward->next = prev->next;

            prev->next = forward;
        }

        return dummy->next;
    }
};