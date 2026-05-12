class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();

        int left = 0;            // left pointer (start)
        int right = n - 1;       // right pointer (end)

        int leftMax = 0;         // left side ka maximum height
        int rightMax = 0;        // right side ka maximum height

        int water = 0;           // total trapped water

        while (left < right) {

            // 🔹 Decide which side controls water
            if (height[left] <= height[right]) {

                // left side ka kaam
                if (height[left] >= leftMax) {
                    // naya left boundary mil gaya
                    leftMax = height[left];
                } else {
                    // pani trap hoga
                    water += leftMax - height[left];
                }

                left++;   // left pointer aage badhao
            } 
            else {

                // right side ka kaam
                if (height[right] >= rightMax) {
                    // naya right boundary
                    rightMax = height[right];
                } else {
                    // pani trap
                    water += rightMax - height[right];
                }

                right--;  // right pointer piche lao
            }
        }

        return water;
    }
};
