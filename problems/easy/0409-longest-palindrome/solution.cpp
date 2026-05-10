class Solution {
public:
    int longestPalindrome(string s) {
        int freq[128] = {0};
        
        // Count frequency
        for(char c : s){
            freq[c]++;
        }
        
        int length = 0;
        bool oddFound = false;
        
        for(int i = 0; i < 128; i++){
            if(freq[i] % 2 == 0){
                length += freq[i];
            }
            else{
                length += freq[i] - 1;  // use even part
                oddFound = true;
            }
        }
        
        if(oddFound) length += 1;  // add one center
        
        return length;
    }
};