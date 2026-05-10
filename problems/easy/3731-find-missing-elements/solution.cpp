class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        
        vector<int> result;
        
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < nums.size() - 1; i++) {
            
            if(nums[i] + 1 != nums[i + 1]) {
                
                for(int j = nums[i] + 1; j < nums[i + 1]; j++) {
                    
                    result.push_back(j);
                }
            }
        }
        
        return result;
    }
};