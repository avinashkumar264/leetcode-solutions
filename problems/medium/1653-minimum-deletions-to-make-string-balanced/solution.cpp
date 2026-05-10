class Solution {
public:
    int minimumDeletions(string s) {

        // Count of 'b' characters seen so far
        int countB = 0;

        // Minimum deletions needed till current index
        int deletions = 0;

        // Traverse the string character by character
        for(int i = 0; i < s.length(); i++) {

            // If current character is 'b'
            if(s[i] == 'b') {

                // Just increase count of 'b'
                countB = countB + 1;
            }
            else {  
                // Current character is 'a'
                // If we see 'a' after some 'b', this can create "ba" pattern
                
                // Option 1: Delete this 'a'
                int deleteCurrentA = deletions + 1;

                // Option 2: Delete all previous 'b'
                int deletePreviousB = countB;

                // Take minimum of both options
                if(deleteCurrentA < deletePreviousB) {
                    deletions = deleteCurrentA;
                } else {
                    deletions = deletePreviousB;
                }
            }
        }

        return deletions;
    }
};