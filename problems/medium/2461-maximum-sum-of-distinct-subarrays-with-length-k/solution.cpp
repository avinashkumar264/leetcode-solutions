#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {

        unordered_set<int> st;

        long long sum = 0;
        long long maxSum = 0;

        int left = 0;

        for (int right = 0; right < nums.size(); right++) {

            // Remove duplicates
            while (st.count(nums[right])) {
                st.erase(nums[left]);
                sum -= nums[left];
                left++;
            }

            // Add new element
            st.insert(nums[right]);
            sum += nums[right];

            // Check window size
            if (right - left + 1 == k) {

                maxSum = max(maxSum, sum);

                // Slide window
                st.erase(nums[left]);
                sum -= nums[left];
                left++;
            }
        }

        return maxSum;
    }
};