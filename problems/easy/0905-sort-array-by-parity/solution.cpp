class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while (l < r) {
            // left already even
            if (nums[l] % 2 == 0) {
                l++;
            }
            // right already odd
            else if (nums[r] % 2 == 1) {
                r--;
            }
            // left odd & right even -> swap
            else {
                swap(nums[l], nums[r]);
                l++;
                r--;
            }
        }
        return nums;
    }
};
