class Solution {
public:
    string reverseStr(string s, int k) {
        
        int size = s.length();
        
        for(int i = 0; i < size; i = i + 2 * k) {
            
            int left = i;
            
            int right = min(i + k - 1, size - 1);
            
            while(left < right) {
                
                swap(s[left], s[right]);
                
                left++;
                right--;
            }
        }
        
        return s;
    }
};