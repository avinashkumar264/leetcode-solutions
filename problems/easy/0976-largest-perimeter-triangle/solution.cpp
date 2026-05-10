class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        // Step 1: Sort in descending order
        sort(nums.begin(), nums.end(), greater<int>());

        // Step 2: Check triples
        for (int i = 0; i < nums.size() - 2; i++) {
            if (nums[i+1] + nums[i+2] > nums[i]) {
                return nums[i] + nums[i+1] + nums[i+2]; // valid triangle
            }
        }

        // Step 3: If no valid triangle
        return 0;
    }
};
