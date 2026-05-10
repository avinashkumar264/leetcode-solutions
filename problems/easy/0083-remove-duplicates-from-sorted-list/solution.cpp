class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        // agar list empty hai
        if (head == nullptr)
            return head;

        ListNode* current = head;

        // traverse list
        while (current != nullptr && current->next != nullptr) {

            // agar duplicate mila
            if (current->val == current->next->val) {
                
                ListNode* temp = current->next;
                current->next = temp->next;
                delete temp;   // duplicate remove
            }
            else {
                // next element ko current bana do
                current = current->next;
            }
        }

        return head;
    }
};