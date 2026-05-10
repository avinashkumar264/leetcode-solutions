class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        // dummy node create
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;
        ListNode* current = head;

        while (current != nullptr) {

            // check duplicate
            if (current->next != nullptr &&
                current->val == current->next->val) {

                int dupValue = current->val;

                // skip all duplicates
                while (current != nullptr &&
                       current->val == dupValue) {
                    current = current->next;
                }

                // connect unique part
                prev->next = current;
            }
            else {
                prev = current;
                current = current->next;
            }
        }

        return dummy->next;
    }
};