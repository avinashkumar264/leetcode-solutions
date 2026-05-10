class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {

        sort(nums.begin(), nums.end());

        long long sum = 0;

        int i = 0;
        int ans = 0;

        for (int j = 0; j < nums.size(); j++) {

            sum += nums[j];

            // required operations > k
            while ((long long)nums[j] * (j - i + 1) - sum > k) {

                sum -= nums[i];
                i++;
            }

            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};