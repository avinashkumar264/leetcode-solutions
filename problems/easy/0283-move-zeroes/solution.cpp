class Solution {
public:
    void moveZeroes(vector<int>& nums) {

        int n = nums.size();

        for (int i = 0; i < n; i++) {

            // agar 0 mila
            if (nums[i] == 0) {

                // aage non-zero dhundo
                for (int j = i + 1; j < n; j++) {

                    if (nums[j] != 0) {

                        // swap
                        swap(nums[i], nums[j]);

                        break;
                    }
                }
            }
        }
    }
};