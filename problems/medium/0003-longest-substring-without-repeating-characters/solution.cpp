class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        unordered_map<char, int> mp;

        int i = 0;
        int j = 0;

        int maxLen = 0;

        while (j < s.length()) {

            // Step 1: Add character
            mp[s[j]]++;

            // Step 2: If duplicate exists
            while (mp[s[j]] > 1) {

                mp[s[i]]--;

                if (mp[s[i]] == 0)
                    mp.erase(s[i]);

                i++;
            }

            // Step 3: Update answer
            maxLen = max(maxLen, j - i + 1);

            j++;
        }

        return maxLen;
    }
};