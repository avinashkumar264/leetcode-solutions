class Solution {
public:
    int characterReplacement(string s, int k) {

        int freq[26] = {0};

        int i = 0;
        int maxFreq = 0;
        int maxLen = 0;

        for (int j = 0; j < s.length(); j++) {

            // add current character
            freq[s[j] - 'A']++;

            // update most frequent character count
            if (freq[s[j] - 'A'] > maxFreq) {
                maxFreq = freq[s[j] - 'A'];
            }

            // check if window invalid
            if ((j - i + 1) - maxFreq > k) {

                freq[s[i] - 'A']--;
                i++;
            }

            // update answer
            if (j - i + 1 > maxLen) {
                maxLen = j - i + 1;
            }
        }

        return maxLen;
    }
};