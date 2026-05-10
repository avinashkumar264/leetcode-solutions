class Solution {
public:
    bool hasAlternatingBits(int n) {
        
        int prev = n & 1;   // get last bit
        n = n >> 1;         // shift right
        
        while(n > 0) {
            int curr = n & 1;   // current last bit
            
            if(curr == prev)    // if same as previous
                return false;
            
            prev = curr;        // update prev
            n = n >> 1;         // shift again
        }
        
        return true;
    }
};