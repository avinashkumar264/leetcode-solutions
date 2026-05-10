#include <vector>
#include <algorithm>   // for max()
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        
        int count = 0;      // current consecutive 1s
        int maxCount = 0;   // maximum consecutive 1s found
        
        for(int i = 0; i < nums.size(); i++) {
            
            if(nums[i] == 1) {
                count++;   // increase streak
                maxCount = max(maxCount, count);  // update max
            }
            else {
                count = 0; // reset streak when 0 found
            }
        }
        
        return maxCount;
    }
};