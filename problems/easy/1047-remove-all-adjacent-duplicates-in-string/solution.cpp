class Solution {
public:
    string removeDuplicates(string s) {

        string result;

        for (int i = 0; i < s.length(); i++) {

            if (!result.empty() && result.back() == s[i]) {
                result.pop_back();      // O(1)
            } 
            else {
                result.push_back(s[i]); // O(1)
            }
        }

        return result;
    }
};