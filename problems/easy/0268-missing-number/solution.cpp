class Solution {
public:
    int missingNumber(vector<int>& nums) {
        
        int n = nums.size();
        
        // Expected sum from 0 to n
        int totalSum = n * (n + 1) / 2;
        
        // Actual sum of array
        int arraySum = 0;
        for (int i = 0; i < n; i++) {
            arraySum += nums[i];
        }
        
        return totalSum - arraySum;
    }
};