class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> st;

        for (int i = 0; i < nums.size(); i++) {

            // agar same element window ke andar mil gaya
            if (st.count(nums[i])) {
                return true;
            }

            st.insert(nums[i]);

            // window size k se bada ho gaya → left element hatao
            if (st.size() > k) {
                st.erase(nums[i - k]);
            }
        }
        return false;
    }
};
