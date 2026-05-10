class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        // agar list empty hai ya single node hai
        if (head == NULL || head->next == NULL)
            return false;

        ListNode* slow = head;
        ListNode* fast = head;

        // traversal
        while (fast != NULL && fast->next != NULL) {
            
            slow = slow->next;          // 1 step
            fast = fast->next->next;    // 2 steps

            // agar dono mil gaye → cycle
            if (slow == fast) {
                return true;
            }
        }

        // fast NULL ho gaya → no cycle
        return false;
    }
};