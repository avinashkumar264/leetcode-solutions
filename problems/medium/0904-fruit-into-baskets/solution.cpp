class Solution {
public:
    int totalFruit(vector<int>& fruits) {

        unordered_map<int, int> mp;

        int i = 0;
        int maxLen = 0;

        for (int j = 0; j < fruits.size(); j++) {

            mp[fruits[j]]++;

            // agar 2 se zyada type ho gaye
            while (mp.size() > 2) {

                mp[fruits[i]]--;

                if (mp[fruits[i]] == 0) {
                    mp.erase(fruits[i]);
                }

                i++;
            }

            maxLen = max(maxLen, j - i + 1);
        }

        return maxLen;
    }
};