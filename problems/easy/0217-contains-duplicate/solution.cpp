class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> st;

        for (int num : nums) {

            // Step 1: Check duplicate
            if (st.count(num)) {
                return true;
            }

            // Step 2: Insert number
            st.insert(num);
        }

        return false;
    }
};